#include <filesystem>
#include <iostream>
#include <sstream>
#include "image_matrix_nontriv.h"

OutOfRamPixelCloud::OutOfRamPixelCloud()
{
}

void OutOfRamPixelCloud::init (unsigned int _roi_label, std::string name)
{
	std::stringstream ssPath;
	ssPath << std::filesystem::temp_directory_path() << "/" << name << _roi_label;
	filepath = ssPath.str();
	pF = fopen(filepath.c_str(), "w+b");

	if (std::setvbuf(pF, nullptr, _IOFBF, 32768) != 0)
		std::cout << "setvbuf failed\n";
}

void OutOfRamPixelCloud::clear()
{
	if (pF)
	{
		fclose(pF);
		pF = nullptr;
		std::filesystem::remove (filepath);
	}
}

void OutOfRamPixelCloud::add_pixel(const Pixel2& p)
{
	fwrite((const void*) &(p.x), sizeof(p.x), 1, pF);
	fwrite((const void*)&(p.y), sizeof(p.y), 1, pF);
	fwrite((const void*)&(p.inten), sizeof(p.inten), 1, pF);
}

size_t OutOfRamPixelCloud::get_size() const
{
	return n_items;
}

Pixel2 OutOfRamPixelCloud::get_at(size_t idx) const
{
	size_t offs = idx * item_size;
	fseek(pF, offs, SEEK_SET);
	Pixel2 px;
	fread((void*)&(px.x), sizeof(px.x), 1, pF);
	fread((void*)&(px.y), sizeof(px.y), 1, pF);
	fread((void*)&(px.inten), sizeof(px.inten), 1, pF);
	return px;
}


WriteImageMatrix_nontriv::WriteImageMatrix_nontriv (const std::string& _name, unsigned int _roi_label)
{
	std::stringstream ssPath;
	ssPath << std::filesystem::temp_directory_path() << "/imagematrix_nontriv" << _roi_label;
	filepath = ssPath.str();
	pF = fopen (filepath.c_str(), "w+b");

	if (std::setvbuf (pF, nullptr, _IOFBF, 32768) != 0) 
		std::cout << "setvbuf failed\n";
}

WriteImageMatrix_nontriv::~WriteImageMatrix_nontriv()
{
	if (pF)
	{
		fclose(pF);
		pF = nullptr;
		std::filesystem::remove (filepath);
	}
}

void WriteImageMatrix_nontriv::allocate (int w, int h, double ini_value)
{
	width = w;
	height = h;

	// Fill the file with 0-s
	auto n = width * height;
	double buf = ini_value;
	for (size_t i=0; i<n; i++)
		fwrite((const void*)&buf, sizeof(buf), 1, pF);
	fflush(pF);
}

void WriteImageMatrix_nontriv::init_with_cloud (const OutOfRamPixelCloud & cloud, const AABB & aabb)
{
	// Allocate space
	allocate(aabb.get_width(), aabb.get_height());
	
	// Fill it with cloud pixels 
	for (size_t i = 0; i < cloud.get_size(); i++)
	{
		const Pixel2 p = cloud.get_at(i);
		auto y = p.y - aabb.get_ymin(),
			x = p.x - aabb.get_xmin();
		set_at (y, x, p.inten);
	}

	// Flush the buffer
	fflush(pF);
}

void WriteImageMatrix_nontriv::set_at(size_t idx, double val)
{
	size_t offs = idx * item_size;
	fseek(pF, offs, SEEK_SET);
	fwrite((const void*)&val, sizeof(val), 1, pF);
	fflush(pF);
}

void WriteImageMatrix_nontriv::set_at (int row, int col, double val)
{
	size_t idx = row * width + col;
	set_at(idx, val);
}

double WriteImageMatrix_nontriv::get_at(size_t idx)
{
	size_t offs = idx * item_size;
	fseek(pF, offs, SEEK_SET);
	double val;
	fread ((void*)&val, sizeof(val), 1, pF);
	return val;
}

double WriteImageMatrix_nontriv::get_at (int row, int col)
{
	size_t idx = row * width + col;
	double val = get_at (idx);
	return val;
}

double WriteImageMatrix_nontriv::get_max()
{
	bool blank = true;
	double retval;

	auto n = width * height;
	double buf = 0.0;
	for (size_t i = 0; i < n; i++)
	{
		fread ((void*)&buf, sizeof(buf), 1, pF);
		if (blank)
		{
			blank = true;
			retval = buf;
		}
		else
			retval = std::max(retval, buf);
	}
	return retval;
}

size_t WriteImageMatrix_nontriv::size()
{
	return width * height;
}

size_t WriteImageMatrix_nontriv::get_width()
{
	return width;
}

size_t WriteImageMatrix_nontriv::get_height()
{
	return height;
}

// Returns chord length at x
size_t WriteImageMatrix_nontriv::get_chlen (size_t col)
{
	bool noSignal = true;
	int chlen = 0, maxChlen = 0;	// We will find the maximum chord in case ROI has holes

	for (int row = 0; row < height; row++)
	{
		if (noSignal)
		{
			if (get_at(row, col) != 0)
			{
				// begin tracking a new chord
				noSignal = false;
				chlen = 1;
			}
		}
		else // in progress tracking a signal
		{
			if (get_at(row, col) != 0)
				chlen++;	// signal continues
			else
			{
				// signal has ended
				maxChlen = std::max(maxChlen, chlen);
				chlen = 0;
				noSignal = true;
			}
		}
	}

	return maxChlen;
}


ReadImageMatrix_nontriv::ReadImageMatrix_nontriv (const AABB & _aabb)
{
	aabb = _aabb;
}

ReadImageMatrix_nontriv::~ReadImageMatrix_nontriv() {}

double ReadImageMatrix_nontriv::get_at (ImageLoader& imloader, size_t pixel_row, size_t pixel_col)
{
	size_t tile_x = imloader.get_tile_x (pixel_col),
		tile_y = imloader.get_tile_y (pixel_row);
	imloader.load_tile (tile_y, tile_x);
	auto& dataI = imloader.get_int_tile_buffer();
	size_t idx = imloader.get_within_tile_idx (pixel_row, pixel_col);
	auto val = dataI[idx];
	return (double)val;
}

double ReadImageMatrix_nontriv::get_at (ImageLoader& imloader, size_t idx)
{
	auto y = aabb.get_ymin() + idx / aabb.get_width(),
		x = aabb.get_xmin() + idx % aabb.get_width();
	double retval = get_at(imloader, y, x);
	return retval;
}

int ReadImageMatrix_nontriv::get_width()
{
	return aabb.get_width();
}

int ReadImageMatrix_nontriv::get_height()
{
	return aabb.get_height();
}




#include "Grid.h"

/*template<typename T>
inline Grid<T>::Grid() :
	mWidth(0), mHeight(0)
{
}*/

template<typename T>
Grid<T>::Grid(size_t width, size_t height)
	: mWidth(width), mHeight(height)
{
	// Resize grid to appropriate size
	mCells.resize(mWidth);
	for (auto& column : mCells)
	{
		column.resize(mHeight);
	}
}

template<typename T>
Grid<T>::~Grid()
{
}

template<typename T>
size_t Grid<T>::getWidth() const
{
	return mWidth;
}

template<typename T>
size_t Grid<T>::getHeight() const
{
	return mHeight;
}

template<typename T>
std::optional<T> Grid<T>::getItemAt(const size_t x, const size_t y) const
{
	if (x >= mWidth || y >= mHeight)
	{
		return std::nullopt;
	}

	return mCells[x][y];
}

template<typename T>
void Grid<T>::setItemAt(const size_t x, const size_t y, T& item)
{
	mCells[x][y].emplace(item);
}

template<typename T>
void Grid<T>::resetAll()
{
	for (int i; i < mWidth; ++i)
	{
		for (int j; i < mHeight; ++j)
		{
			resetAt(i, j);
		}
	}
}

template<typename T>
void Grid<T>::resetAt(const size_t x, const size_t y)
{
	mCells[x][y].reset();
}

/*
template<typename T>
inline bool Grid<T>::isEmpty(const size_t x, const size_t y)
{

	if (getItemAt(x, y) == std::nullopt)
	{
		return true;
	}
	return false;
}


template<typename T>
void Grid<T>::resize(size_t x, size_t y)
{
	// Resize grid to appropriate size
	mCells.resize(mWidth);
	for (auto& column : mCells)
	{
		column.resize(column);
	}
}*/



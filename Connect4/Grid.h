#pragma once

#include <optional>
#include <vector>

template <typename T>
class Grid
{
public:
	// Constructors
	Grid(size_t width, size_t height);

	// Deconstructors
	~Grid();

	// Other
	size_t getWidth() const;
	size_t getHeight() const;
	
	std::optional<T> getItemAt(size_t x, size_t y) const;
	void setItemAt(const size_t x, const size_t y, T &item);
	void resetAll();
	void resetAt(const size_t x, const size_t y);
//	void resize(const size_t x, const size_t y);

private:

	// Member Variables -- Created on stack or heap?
	size_t mWidth;
	size_t mHeight;
	std::vector<std::vector<std::optional<T>>> mCells;		// optional indicates null
};
#include "Grid.inl"
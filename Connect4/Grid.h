#pragma once

#include <optional>
#include <vector>


template <typename T>
using GridType = std::vector<std::vector<std::optional<T>>>;

template <typename T>
class Grid
{
public:
	// Constructors
	//virtual Grid();
	Grid(size_t width, size_t height);

	// Deconstructors
	~Grid();

	// Other
	size_t getWidth() const;
	size_t getHeight() const;

	std::optional<T> getItemAt(size_t x, size_t y) const;
	virtual void setItemAt(const size_t x, const size_t y, T &item);
	void resetAll();
	void resetAt(const size_t x, const size_t y);
//	bool isEmpty(const size_t x, const size_t y);
//	void resize(const size_t x, const size_t y);

// Protected members can be accessed by derived classes
protected:

	// Member Variables -- Created on stack or heap?
	size_t mWidth;
	size_t mHeight;
	GridType<T> mCells;		// optional indicates null
};
#include "Grid.inl"
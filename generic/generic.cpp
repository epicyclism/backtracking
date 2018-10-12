#include "generic.h"

#include <iostream>
#include <vector>

struct move
{
	static size_t sz_;
	size_t pos_ = 0;

	move& operator++()
	{
		++pos_;
		return *this;
	}
	bool operator==(move const& other)
	{
		return pos_ == other.pos_;
	}
	move begin()
	{
		return move(sz_, pos_);
	}
	move end()
	{
		return move(sz_, pos_ + sz_);
	}
	bool at_end() const
	{
		return pos_ == sz_ * sz_;
	}
};

size_t move::sz_ = 0;

class board
{
private:
	std::vector<bool> brd_;
	size_t sz_;

public:
	// board is sz on a side
	board(int sz) : sz_(sz), brd_(sz*sz, false)
	{}
	friend std::ostream& operator<< (std::ostream& ostr, board const& brd)
	{
		size_t cnt{ 0 };
		for (auto b : brd.brd_)
		{
			ostr << (b ? '1' : '0');
			++cnt;
			if (cnt == brd.sz_)
			{
				ostr << "\n";
				cnt = 0;
			}
		}
		return ostr;
	}
	void set(move const& mv)
	{
		brd_[mv.pos_] = true;
	}
	void clear(move const& mv)
	{
		brd_[mv.pos_] = false;
	}
	bool test(int row, int col) const
	{
		return brd_[row * sz_ + col];
	}
	int size() const
	{
		return int(sz_);
	}
	bool valid(move const& mv)
	{
		int row = mv.pos_ / sz_;
		int col = mv.pos_ % sz_;
		// vertical
		for (int r = 0; r < row; ++r)
			if (brd.test(r, col))
				return false;

		// diagonals
		int left = col - row;
		int right = col + row;
		for (int r = 0; r < row; ++r)
		{
			if (left >= 0 && brd.test(r, left))
				return false;
			if (right < brd.size() && brd.test(r, right))
				return false;
			++left;
			--right;
		}

		return true;
	}
	move first_move() const
	{
		move::sz_ = sz_;
		return move();
	}
};

int main()
{
	int n = 0;
	while (n == 0)
	{
		std::cout << "Queens? (more than 0...) : ";
		std::cin >> n;
	}

	board brd(n);
	if (solve(brd, brd.first_move ()))
	{
		std::cout << "Found a solution for " << n << "-queens\n";
		std::cout << brd;
	}
	else
	{
		std::cout << "No solution found for " << n << "-queens\n";
	}
	return 0;
}

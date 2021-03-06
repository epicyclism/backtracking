
#include <iostream>
#include <vector>

#include "generic.h"

struct move_t
{
	static int sz_;
	       int pos_ = 0;

	explicit move_t (int mv ) : pos_ (mv)
	{}
	move_t& operator++()
	{
		pos_ = end();
		return *this;
	}
#if 0
	bool operator!=(move_t const& other) const
	{
		return pos_ != other.pos_;
	}
#endif
	int begin() const
	{
		return pos_ ;
	}
	int end() const
	{
		return (pos_ / sz_ + 1) * sz_ ;
	}
};

int move_t::sz_ = 0;

class board_t
{
private:
	std::vector<bool> brd_;
	int sz_;
	int set_;
public:
	// board is sz on a side
	board_t(int sz) : sz_(sz), brd_(sz*sz, false), set_ (0)
	{}
	friend std::ostream& operator<< (std::ostream& ostr, board_t const& brd)
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
	void set(move_t const& mv)
	{
		brd_[mv.pos_] = true;
		++set_;
	}
	void unset(move_t const& mv)
	{
		brd_[mv.pos_] = false;
		--set_;
	}
	void set(int mv)
	{
		brd_[mv] = true;
		++set_;
	}
	void unset(int mv)
	{
		brd_[mv] = false;
		--set_;
	}
	bool test(size_t row, size_t col) const
	{
		return brd_[row * sz_ + col];
	}
	int size() const
	{
		return sz_;
	}
	bool valid(move_t const& mv)
	{
		return valid(mv.pos_);
	}
	bool valid(int mv)
	{
		auto row = mv / sz_;
		auto col = mv % sz_;

		// horizontal
		for (int c = 0; c < col; ++c)
			if (test(row, c))
				return false;
		// vertical
		for (int r = 0; r < row; ++r)
			if (test(r, col))
				return false;

		// diagonals
		int left = col - row;
		int right = col + row;
		for (int r = 0; r < row; ++r)
		{
			if (left >= 0 && test(r, left))
				return false;
			if (right < sz_ && test(r, right))
				return false;
			++left;
			--right;
		}

		return true;
	}
	move_t first_move() const
	{
		move_t::sz_ = sz_;
		return move_t(0);
	}
	bool solved() const
	{
		return set_ == sz_;
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

	board_t brd(n);
	if (epicyclism::solve(brd, brd.first_move ()))
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

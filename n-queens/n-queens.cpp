// n-queens.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <vector>

class board
{
private:
	std::vector<bool> brd_;
	size_t sz_;

public:
	// board is sz on a side
	board (int sz) : sz_ (sz), brd_ (sz*sz, false)
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
				ostr<< "\n";
				cnt = 0;
			}
		}
		return ostr;
	}
	void set(int row, int col)
	{
		brd_[row * sz_ + col] = true;
	}
	void clear(int row, int col)
	{
		brd_[row * sz_ + col] = false;
	}
	bool test(int row, int col) const
	{
		return brd_[row * sz_ + col];
	}
	int size() const
	{
		return int(sz_);
	}
};

bool non_conflicting(board const& brd, int row, int col)
{
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

bool solve(board& brd, int row)
{
	if (brd.size() == row)
		return true;
	for (int col = 0; col < brd.size(); ++col)
	{
		brd.set(row, col);
		if (non_conflicting(brd, row, col))
		{
			if (solve(brd, row + 1))
				return true;
		}
		brd.clear(row, col);
	}
	return false;
}

int main()
{
	int n = 0;
	while (n == 0)
	{
		std::cout << "Queens? (more than 0...) : ";
		std::cin >> n;
	}

	board brd(n);
	if (solve(brd, 0))
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

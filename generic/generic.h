#pragma once

// first pass generic backtracking solver.
//
// Space is the problem arena. Step is a step in the solution (!)
//
// Space must provide,
//
// bool solved() : if solution complete
// bool valid(Step const& step) : if step would be a valid move
// void set(Step const& step)   : apply the step
// void unset(Step const& step) : undo the step
//
// Step maybe misconstrued at the moment.
//
// 
namespace epicyclism
{
	template<typename Space, typename Step> bool solve(Space& space, Step step)
	{
		if (space.solved())
			return true;

		auto move = step.begin();
		while ( move != step.end())
		{
			if (space.valid(move))
			{
				space.set(move);
				if (solve(space, ++Step(move)))
					return true;
				space.unset(move);
			}
			++move;
		}
		return false; // no solution
	}
}
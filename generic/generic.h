#pragma once

#include <iostream>

namespace epicyclism
{
	template<typename Space, typename State> bool solve(Space& space, State state)
	{
		if (space.solved())
			return true;

		//		for (auto& move : state)
		auto move = state.begin();
		while ( move != state.end())
		{
			if (space.valid(move))
			{
				space.set(move);
				if (solve(space, ++State(move)))
					return true;
				space.unset(move);
			}
			++move;
		}
		return false; // no solution
	}
}
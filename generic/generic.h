#pragma once

template<typename Space, typename State> bool solver(Space& space, State state)
{
	if (state.at_end())
		return true;
	for (auto move : state)
	{
		if (space.valid(move))
		{
			space.set(move);
			if (solver(space, ++State(move)))
				return true;
			space.unset(move);
		}
	}
	return false; // no solution
}
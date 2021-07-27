#include <iostream>
#include <string>

#define FULL	1
#define EMPTY	0
#define NORTH	'N'
#define SOUTH	'S'
#define WEST	'O'
#define EAST 	'E'

using namespace std;

class Grid
{
	private:
		int**	map;
		int		currentXPos = 0;
		int		currentYPos = 0;
		int		xSize = 0;
		int		ySize = 0;

	public:
		Grid(string input)
		{
			int	minXPos = 0, maxXPos = 0;
			int	minYPos = 0, maxYPos = 0;

			// find how far Wall-e goes in each direction
			for (int i = 0; input[i] != '\0'; i++)
			{
				move(input[i]);
				maxXPos = (currentXPos > maxXPos) ? currentXPos : maxXPos;
				minXPos = (currentXPos < minXPos) ? currentXPos : minXPos;
				maxYPos = (currentYPos > maxYPos) ? currentYPos : maxYPos;
				minYPos = (currentYPos < minYPos) ? currentYPos : minYPos;
			}
			// create map
			xSize = maxXPos - minXPos + 1;
			ySize = maxYPos - minYPos + 1;
			map = new int*[xSize];
			for (int i = 0; i < xSize; i++)
				map[i] = new int[ySize];
			// fill map with trash
			for (int x = 0; x < xSize; x++)
				for (int y = 0; y < ySize; y++)
					map[x][y] = FULL;
			// set starting position for Wall-E
			currentXPos = 0 + abs(minXPos);
			currentYPos = 0 + abs(minYPos);
			map[currentXPos][currentYPos] = EMPTY;	// clear starting position
		}
		
		bool	doesCurrentTileHaveTrash()
		{
			
			if (map[currentXPos][currentYPos] == FULL)
				return (true);
			else
				return (false);
		}

		void	cleanCurrentTile()
		{
			map[currentXPos][currentYPos] = EMPTY;
		}

		void	move(char direction)
		{
			if (direction == NORTH)
				currentXPos--;
			else if (direction == SOUTH)
				currentXPos++;
			else if (direction == EAST)
				currentYPos++;
			else if (direction == WEST)
				currentYPos--;
		}
};

int	main()
{
	string			input;
	unsigned int	totalTrash;
	Grid*			grid;

	getline(cin, input);
	grid = new Grid(input);			// init the grid wall-e moves on
	totalTrash = 1;					// starts at 1 to account for the first tile
	for (int i = 0; input[i] != '\0'; i++)
	{
		grid->move(input[i]);
		if (grid->doesCurrentTileHaveTrash())
		{
			grid->cleanCurrentTile();
			totalTrash++;
		}
	}
	cout << totalTrash << endl;
	// TODO: clean up memory
	return (0);
}

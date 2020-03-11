#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Tilemap.h"


class Astar
{
private:
	enum Type
	{
		AIR,
		BLOCK,
		START,
		END,
		VISITED
	};
public:
	Astar(Tilemap& tm);
	void SetDebugTiles();
	void SetStartPos(int x, int y);
	void SetEndPos(int x, int y);
	void DrawPath(sf::RenderTarget& rt);
	bool OnUserCreate();
	bool Solve_AStar(sf::Vector2i startPos, sf::Vector2i endPos, std::vector<std::pair<sf::IntRect, bool>> collisionLayer);
	std::vector<sf::Vector2i> GetPathVector();
	bool OnUserUpdate(sf::RenderTarget& rt, float fElapsedTime);
private:
	Tilemap& tm;
	bool diagonalMovement = true;
	struct sNode
	{
		bool bObstacle = false;			// Is the node an obstruction?
		bool bVisited = false;			// Have we searched this node before?
		float fGlobalGoal;				// Distance to goal so far
		float fLocalGoal;				// Distance to goal if we took the alternative route
		int x;							// Nodes position in 2D space
		int y;
		std::vector<sNode*> vecNeighbours;	// Connections to neighbours
		sNode* parent;					// Node connecting to this node that offers shortest parent
	};
	sNode* nodes = nullptr;
	std::vector<Type> debugDraw;
	int nMapWidth = 25;
	int nMapHeight = 20;
	int nNodeSize = 16;

	sNode* nodeStart = nullptr;
	sNode* nodeEnd = nullptr;
};

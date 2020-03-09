#include "AStar.h"


Astar::Astar(Tilemap& tm)
	:
	tm(tm)
{
	
}

void Astar::SetDebugTiles()
{
	OnUserCreate();
	for (int x = 0; x < nMapWidth; x++)
	{
		for (int y = 0; y < nMapHeight; y++)
		{
			debugDraw.push_back(Type::AIR);
		}
	}
	for (size_t i = 0; i < tm.GetCollisionLayer().size(); i++)
	{
		if (tm.GetCollisionLayer()[i].second)
		{
			debugDraw[i] = Type::BLOCK;
		}
	}
	debugDraw[nMapWidth * nodeStart->y + nodeStart->x] = Type::START;
	debugDraw[nMapWidth * nodeEnd->y + nodeEnd->x] = Type::END;
}

void Astar::SetStartPos(int x, int y)
{
	nodeStart = &nodes[nMapWidth * y + x];
}

void Astar::SetEndPos(int x, int y)
{
	nodeEnd = &nodes[nMapWidth * y + x];
}

void Astar::DrawPath()
{
}

bool Astar::OnUserCreate()
{
	// Create a 2D array of nodes - this is for convenience of rendering and construction
	// and is not required for the algorithm to work - the nodes could be placed anywhere
	// in any space, in multiple dimensions...
	nodes = new sNode[nMapWidth * nMapHeight];
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			nodes[y * nMapWidth + x].x = x; // ...because we give each node its own coordinates
			nodes[y * nMapWidth + x].y = y;
			nodes[y * nMapWidth + x].bObstacle = false;
			nodes[y * nMapWidth + x].parent = nullptr;
			nodes[y * nMapWidth + x].bVisited = false;
		}

	// Create connections - in this case nodes are on a regular grid
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			if (y > 0)
				nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
			if (y < nMapHeight - 1)
				nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
			if (x > 0)
				nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
			if (x < nMapWidth - 1)
				nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);

			// We can also connect diagonally
			if (diagonalMovement)
			{
				if (y > 0 && x > 0)
					nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x - 1)]);
				if (y < nMapHeight - 1 && x>0)
					nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x - 1)]);
				if (y > 0 && x < nMapWidth - 1)
					nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 1)]);
				if (y < nMapHeight - 1 && x < nMapWidth - 1)
					nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 1)]);
			}
		}

	// Manually positio the start and end markers so they are not nullptr
	nodeStart = &nodes[(nMapHeight / 2) * nMapWidth + 1];
	nodeEnd = &nodes[(nMapHeight / 2 - 1) * nMapWidth + nMapWidth - 2];

	return true;
}

bool Astar::Solve_AStar(std::vector<std::pair<sf::IntRect, bool>> collisionLayer)
{
	if (nodes == nullptr)
	{
		nodes = new sNode[nMapWidth * nMapHeight];
	}
	// Reset Navigation Graph - default all node states
	for (int x = 0; x < nMapWidth; x++)
	{
		for (int y = 0; y < nMapHeight; y++)
		{
			nodes[y * nMapWidth + x].bVisited = false;
			nodes[y * nMapWidth + x].fGlobalGoal = INFINITY;
			nodes[y * nMapWidth + x].fLocalGoal = INFINITY;
			nodes[y * nMapWidth + x].parent = nullptr;	// No parents

			if (collisionLayer[nMapWidth * y + x].second)
			{
				nodes[y * nMapWidth + x].bObstacle = true;
			}
		}
	}

	auto distance = [](sNode* a, sNode* b) // For convenience
	{
		return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	};

	auto heuristic = [distance](sNode* a, sNode* b) // So we can experiment with heuristic
	{
		return distance(a, b);
	};

	// Setup starting conditions
	sNode* nodeCurrent = nodeStart;
	nodeStart->fLocalGoal = 0.0f;
	nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

	// Add start node to not tested list - this will ensure it gets tested.
	// As the algorithm progresses, newly discovered nodes get added to this
	// list, and will themselves be tested later
	std::list<sNode*> listNotTestedNodes;
	listNotTestedNodes.push_back(nodeStart);

	// if the not tested list contains nodes, there may be better paths
	// which have not yet been explored. However, we will also stop 
	// searching when we reach the target - there may well be better
	// paths but this one will do - it wont be the longest.
	while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
	{
		// Sort Untested nodes by global goal, so lowest is first
		listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

		// Front of listNotTestedNodes is potentially the lowest distance node. Our
		// list may also contain nodes that have been visited, so ditch these...
		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
			listNotTestedNodes.pop_front();

		// ...or abort because there are no valid nodes left to test
		if (listNotTestedNodes.empty())
			break;

		nodeCurrent = listNotTestedNodes.front();
		nodeCurrent->bVisited = true; // We only explore a node once


		// Check each of this node's neighbours...
		for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
		{
			// ... and only if the neighbour is not visited and is 
			// not an obstacle, add it to NotTested List
			if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
				listNotTestedNodes.push_back(nodeNeighbour);

			// Calculate the neighbours potential lowest parent distance
			float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

			// If choosing to path through this node is a lower distance than what 
			// the neighbour currently has set, update the neighbour to use this node
			// as the path source, and set its distance scores as necessary
			if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
			{
				nodeNeighbour->parent = nodeCurrent;
				nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

				// The best path length to the neighbour being tested has changed, so
				// update the neighbour's score. The heuristic is used to globally bias
				// the path algorithm, so it knows if its getting better or worse. At some
				// point the algo will realise this path is worse and abandon it, and then go
				// and search along the next best path.
				nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
			}
		}
	}

	return true;
}

bool Astar::OnUserUpdate(sf::RenderTarget& rt, float fElapsedTime)
{

				//sf::VertexArray line(sf::LinesStrip,2);
				//line[0].position = sf::Vector2f(x * nNodeSize + nNodeSize / 2, y * nNodeSize + nNodeSize / 2);
				//line[1].position = sf::Vector2f(x * nNodeSize + nNodeSize / 2, y * nNodeSize + nNodeSize / 2);
				//rt.draw(line);

	for (int x = 0; x < nMapWidth; x++)
	{
		for (int y = 0; y < nMapHeight; y++)
		{
			if (nodes[nMapWidth * y + x].bVisited)
			{
				debugDraw[nMapWidth * y + x] = Type::VISITED;
			}

			sf::RectangleShape rect;
			rect.setPosition((x * nNodeSize) + 1, (y * nNodeSize) + 1);
			rect.setSize(sf::Vector2f(15.f, 15.f));
			Type type = debugDraw[nMapWidth * y + x];
			if (type == AIR)
			{
				rect.setFillColor(sf::Color(0, 0, 255, 156));
			}
			else if (type == BLOCK)
			{
				rect.setFillColor(sf::Color(128, 128, 128, 200));
			}
			else if (type == START)
			{
				rect.setFillColor(sf::Color(255, 0, 0, 156));
			}
			else if (type == END)
			{
				rect.setFillColor(sf::Color(0, 255, 0, 156));
			}
			else if (type == VISITED)
			{
				rect.setFillColor(sf::Color(0, 156, 156, 156));
			}
			rt.draw(rect);
		}
	}
	// Draw Path by starting ath the end, and following the parent node trail
	// back to the start - the start node will not have a parent path to follow
	if (nodeEnd != nullptr)
	{
		sNode* p = nodeEnd;
		while (p->parent != nullptr)
		{
			// oma draw
			sf::Vertex line[] = {sf::Vertex(sf::Vector2f(p->x * nNodeSize + nNodeSize / 2, p->y * nNodeSize + nNodeSize / 2) ),
								sf::Vertex(sf::Vector2f(p->parent->x * nNodeSize + nNodeSize / 2,p->parent->y * nNodeSize + nNodeSize / 2) )};
			rt.draw(line, 2, sf::Lines);
			// DrawLine(p->x * nNodeSize + nNodeSize / 2, p->y * nNodeSize + nNodeSize / 2,p->parent->x * nNodeSize + nNodeSize / 2, p->parent->y * nNodeSize + nNodeSize / 2, PIXEL_SOLID, FG_YELLOW);

			// Set next node to this node's parent
			p = p->parent;
		}
	}


	return false;
}

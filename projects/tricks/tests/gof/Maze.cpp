Maze* MazeGame::CreateMaze () {
	Maze* aMaze = new Maze;	// что можно без скобок?
	Room* r1 = new Room(1);
	Room* r2 = new Room(2);
	Door* theDoor = new Door( r1, r2 );
	
	rl->SetSide(North, new Wall);
	rl->SetSide(East, theDoor);
	rl->SetSide(South, new Wall);
	rl->SetSide(West, new Wall);
	
	r2->SetSide(North, new Wall);
	r2->SetSide(East, new Wall);
	r2->SetSide(South, new Wall);
	r2->SetSide(West, theDoor);
	
	return aMaze;
}

Maze* MazeGame::CreateMaze ( const MazeFactory& factory ) {
	Maze* MazeGame::CreateMaze (MazeFactory& factory) {
	Maze* aMaze = factory.MakeMaze();
	
	Room* rl = factory.MakeRoom(l);
	Room* r2 = factory.MakeRoom(2);
	Door* aDoor = factory.MakeDoor(rl, r2);
	
	aMaze->AddRoom(rl) ;
	aMaze->AddRoom(r2);
	
	rl->SetSide(North, factory.MakeWall());
	rl->SetSide(East, aDoor);
	rl->SetSide(South, factory.MakeWall() ) ;
	rl->SetSide(West, factory.MakeWall());
	r2->SetSide(North, factory.MakeWall());
	r2->SetSide(East, factory.MakeWall());
	r2->SetSide(South, factory.MakeWall());
	r2->SetSide(West, aDoor);
	return aMaze;
}

// fabric method
Maze* MazeGame::CreateMaze () {
Maze* aMaze = MakeMaze();
Room* rl = MakeRoom(l);
Room* r2 = MakeRoom(2);
Door* theDoor = MakeDoor(rl, r2);
aMaze->AddRoom(rl);
aMaze->AddRoom(r2);
rl->SetSide(North, MakeWall());
rl->SetSide(East, theDoor);
rl->SetSide(South, MakeWall());
rl->SetSide(West, MakeWall());
r2->SetSide(North, MakeWall());
r2->SetSide(East, MakeWall());
r2->SetSide(South, MakeWall());
r2->SetSide(West, theDoor);
return aMaze;
}

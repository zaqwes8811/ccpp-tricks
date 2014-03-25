enum Direction { North, South, East, West };
class MapSite {
	public : 
		virtual void Enter( ) = 0;
};

class Room : public MapSite {
	public :
		Room( int roomNo );
		
		MapSite* GetSide( Direction ) const;
		void setSide( Direction, MapSite* );
		
		virtual void Enter( );
	private :
		MapSite* _sides[4];
		int _rbonNumber;
};
class Wall : public MapSite {
	public :
		Wall( );
		
		virtual void Enter( );
};

class Door : public MapSite {
	public :
		Door( Room*=0, Room*=0 );
		
		virtual void Enter( );
		Room* OtherSideFrom( Room* );
		
	private :
		Room* _room1;
		Room* _room2;
		bool _isOpen;
};

class Maze {
	public : 
		Maze( );
		
		void AddRoom( Room* );
		Room* RoomNo( int );
		
	private :
		// ...
};

// создает лабиринт
class MazeGame {
	public :
		Maze* CreateMaze ( );
		Maze* CreateMaze ( const MazeFactory& factory );
};

// Abstract factory
class MazeFactory {
	public :
		MazeFactory();
		
		virtual Maze* MakeMaze() const
			{ return new Maze; }
		virtual Wall* MakeWall() const
			{ return new Wall(); }
		virtual Room* MakeRoom( int n ) const
			{ return new Room(n);}
		virtual Door* MakeDoor(Room* r1, Room* r2) const
			{ return new Door(r1, r2);}
};

class EnchantedMazeFactory : public MazeFactory {
	public:
		EnchantedMazeFactory();
		virtual Room* MakeRoom(int n) const
		{ return new EnchantedRoom(n, CastSpell()); }
		virtual Door* MakeDoor(Room* rl, Room* r2) const
		{ return new DoorNeedingSpell(rl, r2); }
	protected:
		Spell* CastSpell() const;
};

// fabric method
class MazeGame {
	public:
		Maze* CreateMaze();
		
		// фабричные методы:
		virtual Maze* MakeMaze() const
			{ return new Maze; }
		virtual Room* MakeRoom(int n) const
			{ return new Room(n); }
		virtual Wall* MakeWall) const
			{ return new Wall; }
		virtual Door* MakeDoor(Room* rl, Room* r2) const
			{ return new Door(rl, r2); }
};

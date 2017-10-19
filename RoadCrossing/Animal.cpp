#include "Animal.h"


//char * Animal::sSoundFile;
//
//Animal::Animal()
//{
//
//}
//
//void Animal::Move()
//{
//}
//
//void Animal::Tell()
//{
//	PlaySound(sSoundFile, NULL, SND_FILENAME);
//}

Animal::Animal()
{

}

Animal::Animal(Direction theDirec) : Obstacle(theDirec) {}

Animal::Animal(int, int)
{
}

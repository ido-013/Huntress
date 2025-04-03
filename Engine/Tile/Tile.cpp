#include "Tile.h"
#include "../Prefab/Prefab.h"
#include "../GameObject/GameObject.h"

std::string const Tile::squareTiles[tileCount] = {
	   "./Assets/Tile/FallGrassTileRect.png",
	   "./Assets/Tile/SpringGrassTileRect.png",
	   "./Assets/Tile/SnowTileRect.png"
};
std::string const Tile::rightTriTiles[tileCount] = {
	   "./Assets/Tile/FallGrassTileRightTri.png",
	   "./Assets/Tile/SpringGrassTileRightTri.png",
	   "./Assets/Tile/SnowTileRightTri.png"
};
std::string const Tile::leftTriTiles[tileCount] = {
	   "./Assets/Tile/FallGrassTileLeftTri.png",
	   "./Assets/Tile/SpringGrassTileLeftTri.png",
	   "./Assets/Tile/SnowTileLeftTri.png"
};
void Tile::ChangeTile(int i)
{
	//square
	GameObject* square = new GameObject("square");
	square->type = GameObject::Square;

	square->AddComponent<TransformComp>();
	square->AddComponent<SpriteComp>();
	square->AddComponent<ColliderComp>();

	square->GetComponent<TransformComp>()->SetScale({ 100, 100 });
	square->GetComponent<TransformComp>()->SetPos({ 0, 0 });

	square->GetComponent<SpriteComp>()->SetTexture(Tile::squareTiles[i]);

	//square->GetComponent<ColliderComp>()->SetCollider();

	Prefab::SavePrefab("Square", square);


	//leftTri
	GameObject* leftTri = new GameObject("leftTri");
	leftTri->type = GameObject::LeftTri;

	leftTri->AddComponent<TransformComp>();
	leftTri->AddComponent<SpriteComp>();
	leftTri->AddComponent<ColliderComp>();

	leftTri->GetComponent<TransformComp>()->SetScale({ 100, 100 });
	leftTri->GetComponent<TransformComp>()->SetPos({ 0, 0 });

	leftTri->GetComponent<SpriteComp>()->SetTexture(Tile::leftTriTiles[i]);

	//leftTri->GetComponent<ColliderComp>()->SetCollider();

	Prefab::SavePrefab("LeftTri", leftTri);


	//rightTri
	GameObject* rightTri = new GameObject("rightTri");
	rightTri->type = GameObject::RightTri;

	rightTri->AddComponent<TransformComp>();
	rightTri->AddComponent<SpriteComp>();
	rightTri->AddComponent<ColliderComp>();

	rightTri->GetComponent<TransformComp>()->SetScale({ 100, 100 });
	rightTri->GetComponent<TransformComp>()->SetPos({ 0, 0 });

	rightTri->GetComponent<SpriteComp>()->SetTexture(Tile::rightTriTiles[i]);

	//rightTri->GetComponent<ColliderComp>()->SetCollider();

	Prefab::SavePrefab("RightTri", rightTri);
}

void Tile::ChangeTile()
{
	ChangeTile(std::rand() % tileCount);
}

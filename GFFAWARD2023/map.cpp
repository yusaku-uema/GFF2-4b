#include"map.h"
#include"character.h"

Map::Map() {
	MapNo = 0;
}

// マップとプレイヤーの描画関数
void Map::GraphDraw(int ScrollX, int ScrollY)
{
    int j, i;
    int MapDrawPointX, MapDrawPointY;     // 描画するマップ座標値
    int DrawMapChipNumX, DrawMapChipNumY; // 描画するマップチップの数

    // 描画するマップチップの数をセット
    DrawMapChipNumX = 1280 / MAP_SIZE + 2;
    DrawMapChipNumY = 720 / MAP_SIZE + 2;

    // 画面左上に描画するマップ座標をセット
    MapDrawPointX = character.getCharacter_X() - (DrawMapChipNumX / 2 - 1);
    MapDrawPointY = character.getCharacter_Y() - (DrawMapChipNumY / 2 - 1);

    // マップを描く
    for (i = -1; i < DrawMapChipNumY; i++)
    {
        for (j = -1; j < DrawMapChipNumX; j++)
        {
            // 画面からはみ出た位置なら描画しない
            if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
                j + MapDrawPointX >= MapData[MapNo].Width || i + MapDrawPointY >= MapData[MapNo].Height) continue;

            // マップデータが０だったら四角を描画する
            if (MapData[MapNo].Data[i + MapDrawPointY][j + MapDrawPointX] == 0)
            {
               /* DrawBox(j * MAP_SIZE + ScrollX, i * MAP_SIZE + ScrollY,
                    j * MAP_SIZE + MAP_SIZE + ScrollX, i * MAP_SIZE + MAP_SIZE + ScrollY,
                    GetColor(255, 0, 0), TRUE);*/
            }
        }
    }
}
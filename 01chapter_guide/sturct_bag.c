#include <stdio.h>
#include <malloc.h>

typedef struct _Bag
{
    //牌子
    char *brand;
    //颜色
    char *color;
} Bag, *PBag;

int main(int argc, char const *argv[])
{
    Bag lvBag;
    lvBag.brand = "lv";
    lvBag.color = "red";

    //   实例化           抽像
    //   对象      <=>    类
    PBag chanelBag = (PBag)malloc(sizeof(PBag));
    chanelBag->brand = "chanel";
    chanelBag->color = "white";

    return 0;
}
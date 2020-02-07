#define RATIO 61
#define HEIGHT 768
#define WIDTH 960
#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 960
#define ROW 9
#define COL 12
#define START_X 114 //偏移量
#define START_Y 100
#define STEP 100  //步数

#define KEY_UP   'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_QUIT 'q'

#define isValid(pos) pos.x>=0&&pos.x<ROW&&pos.y>=0&&pos.y<COL
#define isDes(man,des)  man.x==des.x[0]&&man.y==des.y[0] || \
						man.x==des.x[1]&&man.y==des.y[1] || \
						man.x==des.x[2]&&man.y==des.y[2] || \
						man.x==des.x[3]&&man.y==des.y[3]

typedef enum _DIRECTION DIRECTION;

enum _DIRECTION{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct _POS{
	int x;
	int y;
};

struct _POS man;

struct _BOX_DES_POS{
	int x[4];
	int y[4];
};

struct _BOX_DES_POS des;

typedef enum _PROPS PROPS;

enum _PROPS{
	WALL,
	FLOOR,
	BOX_DES,
	MAN,
	BOX,
	HIT,    //注释此行以实现小人可以把已经到达目的地的箱子推走
	ALL  //ALL在这里表示一共有多少道具,因为枚举元素默认是从0开始数起的 下边定义图片数组的时候大小就可以写ALL 便于代码维护和修改(这是一种高级的技巧)
};
#include "fixed_board.h"

Fixed_Board::Fixed_Board(const int board_pattern)
{
	setFixedBoard(board_pattern);
}

Fixed_Board::~Fixed_Board()
{

}

// 指定盤面をセット
void Fixed_Board::setFixedBoard(const int board_pattern)
{
	switch (board_pattern) {
	case 1:		setBoard(board_pattern_1);		break;
	case 2:		setBoard(board_pattern_2);		break;
	case 3:		setBoard(board_pattern_3);		break;
	case 4:		setBoard(board_pattern_4);		break;
	case 5:		setBoard(board_pattern_5);		break;
	case 6:		setBoard(board_pattern_6);		break;
	case 7:		setBoard(board_pattern_7);		break;
	case 8:		setBoard(board_pattern_8);		break;
	case 101:	setBoard(board_pattern_101);	break;
	case 102:	setBoard(board_pattern_102);	break;
	case 103:	setBoard(board_pattern_103);	break;
	case 104:	setBoard(board_pattern_104);	break;
	case 105:	setBoard(board_pattern_105);	break;
	case 106:	setBoard(board_pattern_106);	break;
	case 107:	setBoard(board_pattern_107);	break;
	case 108:	setBoard(board_pattern_108);	break;
	case 109:	setBoard(board_pattern_109);	break;
	case 110:	setBoard(board_pattern_110);	break;
	case 111:	setBoard(board_pattern_111);	break;
	case 112:	setBoard(board_pattern_112);	break;
	case 113:	setBoard(board_pattern_113);	break;
	case 114:	setBoard(board_pattern_114);	break;
	case 115:	setBoard(board_pattern_115);	break;
	case 116:	setBoard(board_pattern_116);	break;
	case 151:	setBoard(board_pattern_151);	break;
	case 152:	setBoard(board_pattern_152);	break;
	case 153:	setBoard(board_pattern_153);	break;
	case 154:	setBoard(board_pattern_154);	break;
	case 155:	setBoard(board_pattern_155);	break;
	case 156:	setBoard(board_pattern_156);	break;
	case 157:	setBoard(board_pattern_157);	break;
	case 158:	setBoard(board_pattern_158);	break;
	case 159:	setBoard(board_pattern_159);	break;
	case 160:	setBoard(board_pattern_160);	break;
	case 161:	setBoard(board_pattern_161);	break;
	case 162:	setBoard(board_pattern_162);	break;
	case 163:	setBoard(board_pattern_163);	break;
	case 164:	setBoard(board_pattern_164);	break;
	case 165:	setBoard(board_pattern_165);	break;
	case 166:	setBoard(board_pattern_166);	break;
	case 201:	setBoard(board_pattern_201);	break;
	case 202:	setBoard(board_pattern_202);	break;
	case 203:	setBoard(board_pattern_203);	break;
	case 204:	setBoard(board_pattern_204);	break;
	case 205:	setBoard(board_pattern_205);	break;
	case 206:	setBoard(board_pattern_206);	break;
	case 207:	setBoard(board_pattern_207);	break;
	case 208:	setBoard(board_pattern_208);	break;
	case 211:	setBoard(board_pattern_201);	break;
	case 212:	setBoard(board_pattern_202);	break;
	case 213:	setBoard(board_pattern_203);	break;
	case 214:	setBoard(board_pattern_204);	break;
	case 215:	setBoard(board_pattern_205);	break;
	case 216:	setBoard(board_pattern_206);	break;
	case 217:	setBoard(board_pattern_207);	break;
	case 218:	setBoard(board_pattern_208);	break;
	case 301:	setBoard(board_pattern_301);	break;
	case 302:	setBoard(board_pattern_302);	break;
	case 303:	setBoard(board_pattern_303);	break;
	case 304:	setBoard(board_pattern_304);	break;
	case 305:	setBoard(board_pattern_305);	break;
	case 306:	setBoard(board_pattern_306);	break;
	case 307:	setBoard(board_pattern_307);	break;
	case 308:	setBoard(board_pattern_308);	break;
	case 311:	setBoard(board_pattern_301);	break;
	case 312:	setBoard(board_pattern_302);	break;
	case 313:	setBoard(board_pattern_303);	break;
	case 314:	setBoard(board_pattern_304);	break;
	case 315:	setBoard(board_pattern_305);	break;
	case 316:	setBoard(board_pattern_306);	break;
	case 317:	setBoard(board_pattern_307);	break;
	case 318:	setBoard(board_pattern_308);	break;
	case 323:   setBoard(board_pattern_303);    break;
	case 401:	setBoard(board_pattern_401);	break;
	case 402:	setBoard(board_pattern_402);	break;
	case 403:	setBoard(board_pattern_403);	break;
	case 404:	setBoard(board_pattern_404);	break;
	case 405:	setBoard(board_pattern_405);	break;
	case 406:	setBoard(board_pattern_406);	break;
	case 407:	setBoard(board_pattern_407);	break;
	case 408:	setBoard(board_pattern_408);	break;
	case 411:	setBoard(board_pattern_401);	break;
	case 412:	setBoard(board_pattern_402);	break;
	case 413:	setBoard(board_pattern_403);	break;
	case 414:	setBoard(board_pattern_404);	break;
	case 415:	setBoard(board_pattern_405);	break;
	case 416:	setBoard(board_pattern_406);	break;
	case 417:	setBoard(board_pattern_407);	break;
	case 418:	setBoard(board_pattern_408);	break;
	default:
		std::cout << "Error : board_patternの設定に誤りがあります" << std::endl;
		std::cout << std::endl;
		exit(1);
		break;
	}
}
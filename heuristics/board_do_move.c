static uint64_t cubed_board_get_flips_0(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000000000FE;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0101010101010100;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8040201008040200;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_1(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000000000FC;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0202020202020200;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0080402010080400;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_2(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000000000F8;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000010200;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0404040404040400;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000804020100800;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000003;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_3(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000000000F0;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000001020400;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0808080808080800;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000008040201000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000007;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_4(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000000000E0;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000102040800;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x1010101010101000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000080402000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x000000000000000F;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_5(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000000000C0;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000010204081000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x2020202020202000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000804000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x000000000000001F;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_6(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0001020408102000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4040404040404000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x000000000000003F;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_7(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0102040810204000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8080808080808000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x000000000000007F;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_8(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000000000FE00;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0101010101010000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4020100804020000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_9(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000000000FC00;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0202020202020000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8040201008040000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_10(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000000000F800;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000001020000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0404040404040000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0080402010080000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000300;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_11(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000000000F000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000102040000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0808080808080000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000804020100000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000700;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_12(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000000000E000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000010204080000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x1010101010100000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000008040200000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000F00;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_13(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000000000C000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0001020408100000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x2020202020200000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000080400000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000001F00;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_14(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0102040810200000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4040404040400000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000003F00;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_15(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0204081020400000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8080808080800000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000007F00;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_16(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000000000FE0000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0101010101000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x2010080402000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000204;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000101;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_17(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000000000FC0000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0202020202000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4020100804000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000408;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000202;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_18(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000000000F80000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000102000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0404040404000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8040201008000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000030000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000810;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000404;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000201;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_19(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000000000F00000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000010204000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0808080808000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0080402010000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000070000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000001020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000808;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000402;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_20(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000000000E00000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0001020408000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x1010101010000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000804020000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x00000000000F0000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000002040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000001010;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000000804;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_21(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000000000C00000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0102040810000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x2020202020000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000008040000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x00000000001F0000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000004080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000002020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000001008;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_22(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0204081020000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4040404040000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x00000000003F0000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000004040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000002010;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_23(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0408102040000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8080808080000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x00000000007F0000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000008080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000004020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_24(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000FE000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0101010100000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x1008040200000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000020408;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000010101;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_25(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000FC000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0202020200000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x2010080400000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000040810;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000020202;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_26(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000F8000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000010200000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0404040400000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4020100800000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000003000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000081020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000040404;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000020100;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_27(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000F0000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0001020400000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0808080800000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8040201000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000007000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000102040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000080808;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000040201;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_28(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000E0000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0102040800000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x1010101000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0080402000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x000000000F000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000204080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000101010;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000080402;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_29(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00000000C0000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0204081000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x2020202000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000804000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x000000001F000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000408000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000202020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000100804;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_30(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0408102000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4040404000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x000000003F000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000404040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000201008;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_31(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0810204000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8080808000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x000000007F000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000808080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000000402010;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_32(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000FE00000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0101010000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0804020000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000002040810;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000001010101;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_33(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000FC00000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0202020000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x1008040000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000004081020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000002020202;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_34(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000F800000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0001020000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0404040000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x2010080000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000300000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000008102040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000004040404;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000002010000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_35(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000F000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0102040000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0808080000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4020100000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000700000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000010204080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000008080808;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000004020100;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_36(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000E000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0204080000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x1010100000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8040200000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000F00000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000020408000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000010101010;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000008040201;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_37(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x000000C000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0408100000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x2020200000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0080400000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000001F00000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000040800000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000020202020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000010080402;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_38(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0810200000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4040400000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000003F00000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000040404040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000020100804;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_39(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x1020400000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8080800000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000007F00000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000080808080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000040201008;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_40(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000FE0000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0101000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0402000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000204081020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000101010101;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_41(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000FC0000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0202000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0804000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000408102040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000202020202;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_42(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000F80000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0102000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0404000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x1008000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000030000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000810204080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000404040404;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000201000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_43(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000F00000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0204000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0808000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x2010000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000070000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000001020408000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000808080808;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000402010000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_44(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000E00000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0408000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x1010000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4020000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x00000F0000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000002040800000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000001010101010;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000000804020100;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_45(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x0000C00000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0810000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x2020000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8040000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x00001F0000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000004080000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000002020202020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000001008040201;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_46(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x1020000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x4040000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x00003F0000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000004040404040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000002010080402;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_47(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x2040000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x8080000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x00007F0000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000008080808080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000004020100804;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_48(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00FE000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000020408102040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000010101010101;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_49(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00FC000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000040810204080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000020202020202;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_50(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00F8000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0003000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000081020408000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000040404040404;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000020100000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_51(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00F0000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0007000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000102040800000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000080808080808;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000040201000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_52(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00E0000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x000F000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000204080000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000101010101010;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000080402010000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_53(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x00C0000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x001F000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000408000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000202020202020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000100804020100;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_54(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x003F000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000404040404040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000201008040201;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_55(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x007F000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000808080808080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0000402010080402;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_56(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0xFE00000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0002040810204080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0001010101010101;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_57(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0xFC00000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0004081020408000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0002020202020202;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_58(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0xF800000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0300000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0008102040800000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0004040404040404;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0002010000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_59(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0xF000000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0700000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0010204080000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0008080808080808;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0004020100000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_60(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0xE000000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0F00000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0020408000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0010101010101010;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0008040201000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_61(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0xC000000000000000;
    line_mask = line & me;
    bit = uint64_first_bit(line_mask);
    line &= bit - 1ull;
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x1F00000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0040800000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0020202020202020;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0010080402010000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_62(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x3F00000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0040404040404040;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0020100804020100;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}


static uint64_t cubed_board_get_flips_63(
	uint64_t me,uint64_t opp
){
    uint64_t bit;
    uint64_t line;
    uint64_t line_mask;
    uint64_t flipped = 0ull;

    line = 0x7F00000000000000;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0080808080808080;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    line = 0x0040201008040201;
    line_mask = line & me;
    bit = uint64_last_bit(line_mask) & -((bool)line_mask);
    line &= ~((bit << 1) - 1ull);
    flipped |= line & (-((bool)bit)) & (-!((line & opp) ^ line));

    return flipped;
}



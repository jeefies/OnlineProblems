/*
 * Author: Jeefy Fu
 * Email: jeefy163@163.com
 * Description:
 * 		Origin URL: http://noi.openjudge.cn/ch0101/10/
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

char * text = "                ********\n"
"               ************\n"
"               ####....#.\n"
"             #..###.....##....\n"
"             ###.......######              ###                 ###           ###           ###\n"
"                ...........               #...#               #...#         #...#         #...#\n"
"               ##*#######                 #.#.#               #.#.#         #.#.#         #.#.#\n"
"            ####*******######             #.#.#               #.#.#         #.#.#         #.#.#\n"
"           ...#***.****.*###....          #...#               #...#         #...#         #...#\n"
"           ....**********##.....           ###                 ###           ###           ###\n"
"           ....****    *****....\n"
"             ####        ####\n"
"           ######        ######\n"
"##############################################################              ##################################\n"
"#...#......#.##...#......#.##...#......#.##------------------#              #...#......#.##------------------#\n"
"###########################################------------------#              ###############------------------#\n"
"#..#....#....##..#....#....##..#....#....#####################              #..#....#....#####################\n"
"##########################################    #----------#                  ##############    #----------#\n"
"#.....#......##.....#......##.....#......#    #----------#                  #.....#......#    #----------#\n"
"##########################################    #----------#                  ##############    #----------#\n"
"#.#..#....#..##.#..#....#..##.#..#....#..#    #----------#                  #.#..#....#..#    #----------#\n"
"##########################################    ############                  ##############    ############\n"
;

int main() {
	printf(text);
	return 0;
}
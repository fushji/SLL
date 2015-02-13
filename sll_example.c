#include "sll.h"

int main(int argc, char **argv) {

    /* init log lib */
	sll_init("sll_example.log", SLL_LVL_INFO);

    /* log some dummy msg */
	sll_log(SLL_LVL_DEBUG, "debug_lvl message");
	sll_log(SLL_LVL_INFO,  "info_lvl message");
	sll_log(SLL_LVL_ERROR, "error_lvl message");
	
	/* close log lib */
	sll_close();
	
	return 0;
}

//-----------------------------------------------------------------------------//
#include "json.h"
//-----------------------------------------------------------------------------//
static struct treeObject object;
static char *json;
//static char *menu_str_current;
static char menu_str_current[50];
static uint16_t index_menu_str;
//-----------------------------------------------------------------------------//
void jsonInit(char *jsonAssign) {
	#ifdef _WIN32
		sprintf_s(object.parent, "root");
	#else
		sprintf(object.parent, "root");
	#endif
	
	object.parent_index = 4;

	json = jsonAssign;
}
uint16_t addr;
uint16_t i_t, j_t;
//-----------------------------------------------------------------------------//
void get(char *result) {
	char *result_;

	for (i_t = (object.parent_index); i_t > 0; i_t--) {
		if (object.parent[i_t - 1] == ',') {
			break;
		}
	}
	addr = i_t;
	uint16_t json_len;
	bool err = false;

	json_len = strlen(json);
	json_len = json_len - (object.parent_index - addr);

	for (j_t = 0; j_t < json_len; j_t++) {
		err = false;
		for (i_t = addr; i_t < object.parent_index; i_t++) {
			if (json[j_t + i_t - addr] != object.parent[i_t]) {
				err = true;
				break;
			}
		}
		if (!err) {
			break;
		}
	}

	addr = j_t;
	while ((json[addr] != '{') && (json[addr] != '[')) {
		addr++;
	}

	//tag1 -> {}
	//tag2 -> []
	//tag3 -> ""
	uint16_t tag1 = 0, tag2 = 0, tag3 = 0;

	//result = calloc(100, sizeof(char));
	uint16_t dat_index = 0;
	index_menu_str = 0;

	err = false;
	while (!err) {
		if (((json[addr] == '}') || (json[addr] == ']')) && (tag1 == 1)) {
			err = true;
			//break;
		}
		else {
			if (json[addr] == '{') {
				tag1++;
			}
			else {
				if (json[addr] == '}') {
					tag1--;
				}
				else {
					if (json[addr] == '[') {
						tag1++;
					}
					else {
						if (json[addr] == ']') {
							tag1--;
						}
						else {
							if (json[addr] == '"') {
								if (tag3 == 0) {
									tag3 = 1;
								}
								else {
									tag3 = 0;
								}
							}
							else {

							}
						}
					}
				}
			}
			//index_menu_str = 0;
			if ((tag1 == 1) && (tag3 == 1)) {
				//*(result + dat_index) = json[addr];
				result[dat_index] = json[addr];
				menu_str_current[index_menu_str] = json[addr];
				index_menu_str++;
				dat_index++;
			}
			addr++;
		}
	}
	result[dat_index] = '"';
	//menu_str_current = result;
	//index_menu_str = dat_index + 1;
	menu_str_current[index_menu_str] = '"';
	index_menu_str++;
}
//-----------------------------------------------------------------------------//
bool select(uint8_t index) {
	//Find address of string index
	uint16_t i = 0;
	uint8_t detect = 0;
	bool err = false;
	while ((i < index_menu_str) && (!err)) {
		if (menu_str_current[i] == '"') {
			detect++;
			if ((detect - 1) == index) {
				err = true;
			}
		}
		i++;
	}
	//	if(err){
	//		return false;
	//	}

	//Split ',' 
	object.parent[object.parent_index] = ',';
	object.parent_index++;

	//Add menu str select to parent
	while (menu_str_current[i] != '"') {
		object.parent[object.parent_index] = menu_str_current[i];
		object.parent_index++;
		i++;
	}

	return true;
}
//-----------------------------------------------------------------------------//
bool jReturn(void) {
	while (object.parent[object.parent_index - 1] != ',') {
		object.parent[object.parent_index - 1] = 0;
		object.parent_index--;
	}
	object.parent[object.parent_index - 1] = 0;
	object.parent_index--;

	return true;
}
//-----------------------------------------------------------------------------//
char get1(char *json, char *name, char *result) {
	uint16_t len1 = strlen(name);
	uint16_t i, j;
	uint16_t len_json = strlen(json);
	bool err = false;
	for (i = 0; i < len_json - 5; i++) {
		if ((json[i] == 'n') && (json[i + 1] == 'a') && (json[i + 2] == 'm') && (json[i + 3] == 'e')) {
			err = false;
			for (j = 0; j < len1; j++) {
				if (json[i + 7 + j] != *(name + j)) {
					err = true;
					break;
				}
			}
			if (!err) {
				uint8_t start = i + 7 + j + 10, temp_ = 0, rec = 0;
				err = false;
				if (json[start] == '[') {
					while (!err) {
						if ((json[start] != '[') && (json[start] != ']')) {
							*(result + rec) = json[start];
							rec++;
						}
						if (json[start] == ']') {
							err = true;
						}
						start++;
					}
				}
				else {
					while (!err) {
						if ((json[start] != '[') && (json[start] != ']')) {
							*(result + rec) = json[start];
							rec++;
						}
						if (json[start] == '\"') {
							temp_++;
							if (temp_ == 2) err = true;
						}
						start++;
					}
				}


				return (i + 7 + j);
			}
		}
	}
	return 0;
}
//-----------------------------------------------------------------------------//
//-----------------------------------------------------------------------------//
// #include <stdio.h>
// #include <stdlib.h>

#define CANVAS_WIDTH 296
#define CANVAS_HEIGHT 128

#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>
#include <stdlib.h>

// Get datetime (unix timestamp)
#define TEST_NAME          "drawRectangle"
#define TEST_FUNC         drawRectangle

 unsigned char canvas_data[CANVAS_WIDTH * CANVAS_HEIGHT];


void create_byte_array(int x_start,int x_end,int y_start,int y_end)
{
    // Set the background to white (255)
    for (int i = 0; i < CANVAS_WIDTH * CANVAS_HEIGHT; ++i) {
        canvas_data[i] = 255;
    }

    for (int y = y_start; y < y_end; ++y) {
        for (int x = x_start; x < x_end; ++x) {
            canvas_data[y * CANVAS_WIDTH + x] = 0;
        }
    }
}

int drawRectangle( lua_State *vm ) {

    int nargs = lua_gettop( vm );
    int x_start;
    int x_end;
    int y_start;
    int y_end;

    if( nargs != 4 ) {
        return 0;
    }

    if( lua_isnumber( vm, 1 ) ) 
    {
        x_start = lua_tointeger( vm, 1 );
    }

    if (lua_isnumber(vm, 2))
    {
        x_end = lua_tointeger(vm, 2);
    }

    if (lua_isnumber(vm, 3))
    {
        y_start = lua_tointeger(vm, 3);
    }

    if (lua_isnumber(vm, 4))
    {
        y_end = lua_tointeger(vm, 4);
    }

    printf("Received Text: %d, %d, %d, %d\n", x_start,x_end,y_start, y_end );


    create_byte_array(x_start,x_end,y_start,y_end);
}



int main(int argc, char *argv[])
{
    memset(canvas_data, CANVAS_WIDTH * CANVAS_HEIGHT, 0);

    // Print the received text
    printf("Received Text: %s\n", argv[1]);

    static luaL_Reg shrooly_lua_func_list[] = {
        {TEST_NAME, TEST_FUNC},
        {NULL, NULL}};

    // Create a Lua state
    lua_State *L = luaL_newstate();

    // Load Lua standard libraries
    luaL_openlibs(L);

    lua_getglobal(L, "_G");
    luaL_setfuncs(L, shrooly_lua_func_list, 0);
    lua_pop(L, 1);


    /*For manual purpuses*/
    const char *luaScript =
        "print('Hello from Lua!')\n   \
         drawRectangle(50,70,20,40)";

    // Execute a Lua script
    int result = luaL_dostring(L, argv[1]);


    // Check for errors in Lua script execution
    if (result != LUA_OK)
     {
        printf("Error executing Lua script: %s\n", lua_tostring(L, -1));
    }


  // Close the Lua state
    lua_close(L);

    // Open a binary file for writing
    FILE *file = fopen("canvas_data.bin", "wb");

    if (!file) 
    {
        printf("Failed to open file for writing.\n");
        return 1;
    }

    // Write the byte array to the file
    fwrite(&canvas_data, sizeof(unsigned char), CANVAS_WIDTH * CANVAS_HEIGHT, file);

    // Close the file
    fclose(file);


    return 0;
}
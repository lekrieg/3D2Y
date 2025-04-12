#include "EditorApplication.h"

int main()
{
	editor::EditorApplication editor("config.txt", "assets.txt");
	editor.Run();
}

#pragma once

enum class SortingLayers
{
	Background,
	Foreground,
	UI,
	Default,
};

enum class SceneIds
{
	None = -1,
	Dev1,
	Dev2,
<<<<<<< HEAD
	SelectStage,
=======
	VsScene,
	Title,
	Select,
>>>>>>> origin/develop
	Count,
};

enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,
	Custom,
};

enum class Sides
{
	Left,
	Right,
	None,
};

enum class ChkPlayer
{
	FirstP,
	SecondP,
};

enum class PlayMode
{
	Single,
	Multi,
};
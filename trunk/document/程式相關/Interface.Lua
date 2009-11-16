
GameName = "Tempo Timing Fight Game"
--主畫面
Main = {
	BackGround = { Pic16_10 = "BG1.png",
			Pic4_3 = "BG43_1.PNG"},
	Item1 = "GameSet",
	Item2 = "PracticeMode",
	Item3 = "ArcadeMode",
	Item4 = "StoryMode",
	Item5 = "VSMode",
	Item6 = "Replayer",
	Item7 = "About",
	Item8 = "Exit",
	Exit = {
	NormalPic = "",
	SelectPic = "",
	EnterPic = "",
		},
	ExitRect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00,}
	}
--字型
TTF = {
	FilePic = "",
	NormalColor = {a= 255, r= 255, g= 255, b= 255},
	SelectColor = {a= 255, r= 255, g= 255, b= 255},
	EnterColor = {a= 255, r= 255, g= 255, b= 255}
	}
--[按鈕]遊戲設定
GameSet = {
	Word = "Option",
	BackGround = { Pic16_10 = "BG2.png",
			Pic4_3 = "BG43_2.PNG"},
	NormalPic = "GameSet.png",
	SelectPic = "GameSet.png",
	EnterPic = "GameSet.png",
	Rect = {left = 400,
		right = 600,
		top = 100,
		bottom = 200,};
	ReturnRect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00,};
	Item1 = "BGMBar",
	Item2 = "SoundEffectBar",
	Item3 = "PKRoundBar",
	Item4 = "AIRank",
	Item5 = "KeyBoardSet",
	Item6 = "ConstTempo",
	Item7 = "TempoEnble",
	Item8 = "return"
	}
--[橫棒]BGM大小
BGMBar = {
	Word = "BackGround Music",
	BarNormalPic = "",
	BarSelectPic = "",
	PointerNormalPic = "",
	PointerSelectPic = "",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	Y = 00,
	LeftX = 00,
	RightX = 00
	}
--[橫棒]音效大小
SoundEffectBar = {
	Word = "SoundEffect",
	BarNormalPic = "",
	BarSelectPic = "",
	PointerNormalPic = "",
	PointerSelectPic = "",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	Y = 00,
	LeftX = 00,
	RightX = 00
	}
--[橫棒]對打回合
PKRoundBar = {
	Word = "PK Round",
	BarNormalPic = "",
	BarSelectPic = "",
	PointerNormalPic = "",
	PointerSelectPic = "",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	Y = 00,
	LeftX = 00,
	RightX = 00
	}
--[橫棒]AI難度
AIRank = {
	Word = "AI Rank",
	BarNormalPic = "",
	BarSelectPic = "",
	PointerNormalPic = "",
	PointerSelectPic = "",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	Y = 00,
	LeftX = 00,
	RightX = 00
	}
--[按鈕]按鍵設定
KeyBoardSet = {
	Word = "KeyBoardSet",
	NormalPic = "",
	SelectPic = "",
	EnterPic = "",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	}
--[橫棒]固定節奏值為X%
ConstTempo = {
	Word = "Constant Tempo",
	BarNormalPic = "",
	BarSelectPic = "",
	PointerNormalPic = "",
	PointerSelectPic = "",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	Y = 00,
	LeftX = 00,
	RightX = 00
	}
--[二選一]節奏值是否影響攻擊力。
TempoEnble = {
	Word = "Tempo Enable",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00,};
	Option1 = "",
	Option1Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	Option2 = "",
	Option2Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	}
--[按鈕]練習模式
PracticeMode = {
	Word = "Practice Mode",
	BackGround = { Pic16_10 = "",
			Pic4_3 = ""},
	NormalPic = "PracticeMode.png",
	SelectPic = "PracticeMode.png",
	EnterPic = "PracticeMode.png",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	}
--選擇人物
SelectRole = {
	Word = "SelectRole",
	NormalPic = "",
	SelectPic = "",
	EnterPic = "",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	Max = 40,
	RolePos =
	function (index)
		--計算Rect並回傳
		local Left = index % 100
		local Right = index % 100 + 100
		local Top = (index - (index % 10)) * 100
		local Bottom = (index - (index % 10)) * 100 + 100
		return Left,Right,Top,Bottom
	end,
	}
--選擇場景
SelectBG = {
	Word = "SelectBG",
	NormalPic = "",
	SelectPic = "",
	EnterPic = "",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	Max = 20,
	BGPos =
	function (index)
		--計算Rect並回傳
		local Left = index % 200
		local Right = index % 200 + 200
		local Top = (index - (index % 10)) * 200
		local Bottom = (index - (index % 10)) * 100 + 200
		return Left,Right,Top,Bottom
	end,
	}
--[按鈕]連打模式
ArcadeMode = {
	Word = "Arcade Mode",
	BackGround = { Pic16_10 = "",
			Pic4_3 = ""},
	NormalPic = "ArcadeMode.png",
	SelectPic = "ArcadeMode.png",
	EnterPic = "ArcadeMode.png",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	}
--[按鈕]故事模式
StoryMode = {
	Word = "Story Mode",
	BackGround = { Pic16_10 = "",
			Pic4_3 = ""},
	NormalPic = "StoryMode.png",
	SelectPic = "StoryMode.png",
	EnterPic = "StoryMode.png",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	}
--[按鈕]對打模式
VSMode = {
	Word = "VS Mode",
	BackGround = { Pic16_10 = "",
			Pic4_3 = ""},
	NormalPic = "VSMode.png",
	SelectPic = "VSMode.png",
	EnterPic = "VSMode.png",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	}
--[按鈕]重播
Replayer = {
	Word = "Replayer",
	BackGround = { Pic16_10 = "",
			Pic4_3 = ""},
	NormalPic = "VSMode.png",
	SelectPic = "VSMode.png",
	EnterPic = "VSMode.png",
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	}
--[按鈕]關於製作群
About = {
	Word =
	[[
	程式：
	天亮damody
	翼光城W.S.C
	美術：

	]],
	Rect = {left = 00,
		right = 00,
		top = 00,
		bottom = 00};
	}

--[[
[按鈕]遊戲設定
	[橫棒]BGM大小
		0~100%
	[橫棒]音效大小
		0~100%
	[橫棒]對打回合
		1~7
	[橫棒]AI難度
		簡易、普通、難
	[按鈕]按鍵設定
		Player1
			上、下、左、右、A,B,C,D
		Player2
			上、下、左、右、A,B,C,D
	[橫棒]固定節奏值為X%
	[二選一]節奏值是否影響攻擊力。
[按鈕]練習模式
	選擇人物
	選擇場景
從這裡開始，風格由場景控制
	初始化戰鬥資訊
	初始化rp錄製器
	開始戰鬥
	儲存rp
		自行離開
		戰鬥結束
		重新開始
從這裡開始，風格由主畫面控制
	回到選擇人物
[按鈕]連打模式
	選擇人物
從這裡開始風格由隨機到的人物的預設場景控制
	初始化戰鬥資訊
	初始化rp錄製器
	開始戰鬥
	儲存rp
		自行離開
		戰鬥結束
		儲存目前進度
		重新開始這一場戰鬥
	戰鬥迴圈
		失敗選單
			重新開始這一場戰鬥
			離開
			命名這一場戰鬥的rp
	全打贏時顯示製作群
	回到選人畫面
[按鈕]故事模式
	顯示所有故事供玩家選擇
	載入故事並顯示故事
	從這開始流程與畫面風格由故事腳本決定。
	可存檔
	全破
[按鈕]離開遊戲
	清掉所有內存離開
[按鈕]對打模式
	[按鈕]與電腦對打
		一打一
		一打n
	[按鈕]與玩家對打
		p1 vs p2
		p1,p2 vs com,com
	[按鈕]與tcp/ip連線對打
		p1 vs p2
		p1,p2 vs p3
		p1,p2 vs com
		p1,p2 vs com,com
		p1,p2 vs p3,p4
		p1,p2 vs p3,com
[按鈕]關於製作群
[按鈕]觀看記錄檔
	[清單]rp清單
]]--

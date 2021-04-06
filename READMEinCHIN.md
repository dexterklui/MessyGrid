Identification of member:
Name: Lui Ka On (UID: 3035074610) 
Name: Ye Zhongzheng(UID:3035782176)

Description:
這是一個移動格子的遊戲，玩家。然後系統會自動生成一個順序混亂的格子順序，玩家然後需要多次手動輸入想移動的格子編號，直到版面上的所有格子的數字按照順序排列。

Rules:
1.	首先，玩家需要先選擇版面的尺寸（例如是3*3或者4*3）。
2.	然後，版面上會出現一個空出來的格子，玩家需要選擇移動空格周圍（上下左右）的一個格子，被移動的格子會被移動到空格的位置
3.	直到版面上的所有格子的數字按照順序排列，遊戲結束。
4.	玩家可以隨時保存遊戲進度，並且為遊戲進度命名。
5.	玩家可以讀取已保存的遊戲進度，並繼續之前的遊戲。
6.	系統會自動紀錄玩家移動格子的移動次數，以及進行遊戲的時間。
7.	玩家每次結束遊戲後，根據所用時間或者所用步數，系統會在相應的格式下生成排行榜（例如3*3排行榜），來顯示玩家的成績。

Features:
1.	根據玩家的喜好，生成特定尺寸的版面。
2.	根據玩家輸入的格式，自動生成混亂的board arrangement：在系統中生成一個random number，將順序正常的cell打亂，將生成的混亂grid輸出到玩家界面。（R1: Generation of random game sets or events）
3.	移動cell：玩家輸入“上下左右W S A D”然後來控制cell的移動 （R3: Dynamic memory management）
4.	在玩家交互界面，更新board的現時狀態。
5.	保存遊戲進度（R2: Data structures for storing game status & R4: File input/output）
6.	讀取遊戲進度（R5: Program codes in multiple files）
7.	排行榜，保存玩家成績：sort


abc


Others：
board arrangement，grid，cell

系統首先會生成一個順序正常的格子，並存儲在array內。然後系統再次生成一個大於n的隨機數字，根據這個隨機數字，


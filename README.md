# Paging-management
實作Memory中的分頁法，包括FIFO(先進先出), LRU(最近罕用), ARB(附加參考位元), SC(二次機會), LFU(最不常使用), MFU(最常使用)。

## 開發平台
Win10
<br>
<br>

## 使用開發環境
Dev C++
<br>
<br>

## 使用方式
將input檔放至當前目錄<br>
編譯

      OS_project3.cpp
或

      OS_project3_v2.cpp

之後執行<br>
輸入input檔名後<br>
程式會產出結果於 input檔名_output.txt 檔案中<br>
<br> 
<br>

## input檔格式
第一行為page Frame個數(範圍為1-10)<br>
第二行為各個Page Reference的次序 (範圍為0-100)
<br> 
<br>

## output檔格式
顯示每種page Replacement 之 Page Fault 和 Page Replace的次數
<br>
<br>

## v1及v2版本介紹

v1實作FIFO, LRU, ARB, SC, LFU, MFU<br>

v2中的LFU及MFU則有所更動<br>

(1)在LFU的counter一樣時用FIFO判斷。<br>
讀入input2.txt檔，output2(LFU+FIFO).txt<br>
(2)在MFU的counter一樣時用LIFO判斷。<br>
讀入input3.txt檔，output3(MFU+LIFO).txt<br>
<br>
<br>

## 規則細節說明

* Additional Reference Bits : <br>
本規定10 Pages作一次shift，<br>
但會因為太久才做一次shift，看不出來結果變化有何特殊，<br>
因此改為每個page均做一次shift。<br>

* Second Chance的規則：<br>
規則1： 每個頁框均有一對應參考位元，其初始值為0。當某個頁框被存取時，其相對參考位元便被設定為1。<br>
規則2： 在給予第二次機會同時，將其參考位元設定為0，並將此頁框的時間標記設定為現在的時間。<br>

      1 1 F (1,0,0) //規則1
      2 21 F (1,1,0) //規則1
      3 321 F (1,1,1) //規則1
      4 432 F (1,0,0) // 由於發生 page fault 要找到下一個被替換的，
      // 但是三個都是1 因此將3個設定為0 並且將置換的設為1
      1 143 F (1,1,0)
      2 214 F (1.1.1)
      5 521 F (1,0,0) // 由於發生 page fault 要找到下一個被替換的 ，但是三個
      // 都是1因此 將3個設定為0 並且 將置換的設為1
      1 521 (1,0,1) // reference 到 修改為 1
      2 521 (1,1,1) // reference 到 修改為 1
      3 352 F (1,0,0) //
      4 435 F (1,1,0) //
      5 435 (1,1,1) //規則1
      Page Fault = 9 Page Replaces = 6 Page Frames = 3

* 在Least Frequently Used Page Replacement 以及 Most Frequently Used Page Replacement <br>
發生兩個以上counter數相同時<br>
依照LRU的規則決定要替換掉的page<br>

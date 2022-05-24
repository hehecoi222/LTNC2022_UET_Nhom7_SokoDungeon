# Nhóm 7: SokoDungeon Bài tập lớn: 2122HK2 - Lập trình nâng cao - INT2215 22 
![Build](https://github.com/hehecoi222/LTNC2022_UET_Nhom7_SokoDungeon/actions/workflows/cmake.yml/badge.svg)

## Mục lục

1. [Tổng quan](#tổng-quan)
2. [Các chức năng](#các-chức-năng)
3. [Cách thức chạy](#cách-thức-chạy-chương-trình)
4. [Phân công công việc](#phân-công-công-việc)
5. [Tham khảo](#tham-khảo)

## Tổng quan

Trò chơi SokoDungeon, bài tập lớn của nhóm 7, môn học Lập trình nâng cao INT2215 22 học kì 2 năm học 2021-2022. Nhóm 7 gồm 3 thành viên: Chu Ngọc Vương, Nguyễn Trung Hiếu, Bùi Anh Dũng cùng hoàn thành bài tập.

Về SokoDungeon, cách chơi khá giống game cổ điển Sokoban (Đẩy thùng), người chơi sẽ phải tìm cách đưa các thùng về các vị trí đã định. Bên cạnh đó còn có một nhân vật sẽ tiến tới người và chặn đường hoàn thành nhiệm vụ chính.

## Các chức năng

- Có các nhân vật như người chơi chính, kẻ chặn đường
- Có các trạng thái vào game, ở menu
- Có đọc map từ file, chuyển nhiều map
- Có lưu các bước đi, trở lại các bước đi
- Có phân tách các đối tương, chức năng ra các file code cho thuận tiện xử lý
- Có âm nhạc, hình ảnh, chức năng của menu
- Có thể lưu được game sau khi thoát
- Có Highscore cho người chơi

## Cách thức chạy chương trình

### Cách 1:

1. Clone repo này hoặc tải dưới dạng ZIP, giải nén ra
2. Chạy `Makefile.bat`, trò chơi sẽ tự động build và chạy

### Cách 2:

1. Clone repo này hoặc tải dưới dạng ZIP, giải nén ra
2. Mở cmd hoặc terminal/powershell gõ các lệnh
> `g++ src/*.cpp -g -std=c++11 -Ilib/SDL2/include/SDL2 -Iinclude -Llib/SDL2/lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o build/sokodugeon.exe`
3. Vào thư mục build, mở file `sokodungeon.exe`

## Phân công công việc

1. Về phần Chu Ngọc Vượng
  + Nhân vật 
  + Menu
  + Hình ảnh

2. Về phần Nguyễn Trung Hiếu
  + Enemy
  + Box
  + Save game

3. Về phần Bùi Anh Dũng
  + Map
  + Âm thanh
  + Level design

*Phần còn lại các thành viên cùng hoàn thiện*

## Tham khảo

- Cách thức cài đặt thư viện/tìm kiếm các resources: [Lazyfoo](https://www.lazyfoo.net/tutorials/SDL) và [WillUsher](https://www.willusher.io/pages/sdl2/)
- Cách chia tách file, capping fps: [Let's make game](https://www.youtube.com/c/CarlBirch)
- Resources: [Itch.io](https://www.itch.io)

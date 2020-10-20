# Nhập môn phát triển game
## MARIO BROS 3
### Chi tiết các lần commit
- 14-10: Load map từ file tmx, chưa set camera.
- 16-10: Load mario lẹn map, camera dựa trên code của thầy.
- 19-10: Load map bằng txt.
- 20-10: Sửa hàm draw để flip và scale
```bash
Vấn đề:
- Set bbox của block 48x48 nhưng draw sprite thì scale x3.
=> Khi draw thì sprite và bbox bị lệch
```

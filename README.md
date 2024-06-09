# clang-project
2024-1 clang project

# 주의사항

- `malloc`과 같이 동적할당하거나 할 때 세그폴드 뜨지 않게 조심! (할당이 안된경우 에러 반환)
- map.subjects[id]를 쓸때는 항상 이게 0이 아닌지 주의!

- 실행 방법
gcc main.c subject.c prereq.c timetable.c -o main
./main.exe
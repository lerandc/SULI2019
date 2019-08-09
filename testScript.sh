prismatic --help
#test Multislice
printf "Begin multislice testing. \n"
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a m -ns 1 -o test1.h5 > test1.out
printf "Test %d/45 complete \n" 1
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a m -ns 1 -o test2.h5 > test2.out
printf "Test %d/45 complete \n" 2
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a m -ns 1 -o test3.h5 > test3.out
printf "Test %d/45 complete \n" 3
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a m -ns 1 -o test4.h5 -px 0.05 -py 0.2  > test4.out
printf "Test %d/45 complete \n" 4
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a m -ns 1 -o test5.h5 -px 0.05 -py 0.2 > test5.out
printf "Test %d/45 complete \n" 5
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a m -ns 1 -o test6.h5  -px 0.05 -py 0.2 > test6.out
printf "Test %d/45 complete \n" 6
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a m -ns 1 -o test7.h5 -px 0.2 -py 0.05 > test7.out
printf "Test %d/45 complete \n" 7
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a m -ns 1 -o test8.h5 -px 0.2 -py 0.05 > test8.out
printf "Test %d/45 complete \n" 8
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a m -ns 1 -o test9.h5  -px 0.2 -py 0.05 > test9.out
printf "Test %d/45 complete \n" 9

#test PRISM
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 4 -fy 4 -o test10.h5 > test10.out
printf "Test %d/45 complete \n" 10
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 4 -fy 4 -o test11.h5 > test11.out
printf "Test %d/45 complete \n" 11
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 4 -fy 4 -o test12.h5 > test12.out
printf "Test %d/45 complete \n" 12
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 4 -fy 4 -px 0.05 -py 0.2 -o test13.h5 > test13.out
printf "Test %d/45 complete \n" 13
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 4 -fy 4 -px 0.05 -py 0.2 -o test14.h5 > test14.out
printf "Test %d/45 complete \n" 14
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 4 -fy 4 -px 0.05 -py 0.2 -o test15.h5 > test15.out
printf "Test %d/45 complete \n" 15
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 4 -fy 4 -px 0.2 -py 0.05 -o test16.h5 > test16.out
printf "Test %d/45 complete \n" 16
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 4 -fy 4 -px 0.2 -py 0.05 -o test17.h5 > test17.out
printf "Test %d/45 complete \n" 17
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 4 -fy 4 -px 0.2 -py 0.05 -o test18.h5 > test18.out
printf "Test %d/45 complete \n" 18

prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 6 -fy 4 -o test19.h5 > test19.out
printf "Test %d/45 complete \n" 19
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 6 -fy 4 -o test20.h5 > test20.out
printf "Test %d/45 complete \n" 20
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 6 -fy 4 -o test21.h5 > test21.out
printf "Test %d/45 complete \n" 21
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 6 -fy 4 -px 0.05 -py 0.2 -o test22.h5 > test22.out
printf "Test %d/45 complete \n" 22
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 6 -fy 4 -px 0.05 -py 0.2 -o test23.h5 > test23.out
printf "Test %d/45 complete \n" 23
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 6 -fy 4 -px 0.05 -py 0.2 -o test24.h5 > test24.out
printf "Test %d/45 complete \n" 24
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 6 -fy 4 -px 0.2 -py 0.05 -o test25.h5 > test25.out
printf "Test %d/45 complete \n" 25
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 6 -fy 4 -px 0.2 -py 0.05 -o test26.h5 > test26.out
printf "Test %d/45 complete \n" 26
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 6 -fy 4 -px 0.2 -py 0.05 -o test27.h5 > test27.out
printf "Test %d/45 complete \n" 27

prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 4 -fy 5 -o test28.h5 > test28.out
printf "Test %d/45 complete \n" 28
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 4 -fy 5 -o test29.h5 > test29.out
printf "Test %d/45 complete \n" 29
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 4 -fy 5 -o test30.h5 > test30.out
printf "Test %d/45 complete \n" 30
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 4 -fy 5 -px 0.05 -py 0.2 -o test31.h5 > test31.out
printf "Test %d/45 complete \n" 31
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 4 -fy 5 -px 0.05 -py 0.2 -o test32.h5 > test32.out
printf "Test %d/45 complete \n" 32
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 4 -fy 5 -px 0.05 -py 0.2 -o test33.h5 > test33.out
printf "Test %d/45 complete \n" 33
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 4 -fy 5 -px 0.2 -py 0.05 -o test34.h5 > test34.out
printf "Test %d/45 complete \n" 34
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 4 -fy 5 -px 0.2 -py 0.05 -o test35.h5 > test35.out
printf "Test %d/45 complete \n" 35
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 4 -fy 5 -px 0.2 -py 0.05 -o test36.h5 > test36.out
printf "Test %d/45 complete \n" 36

prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 7 -fy 5 -o test37.h5 > test37.out
printf "Test %d/45 complete \n" 37
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 7 -fy 5 -o test38.h5 > test38.out
printf "Test %d/45 complete \n" 38
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 7 -fy 5 -o test39.h5 > test39.out
printf "Test %d/45 complete \n" 39
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 7 -fy 5 -px 0.05 -py 0.2 -o test40.h5 > test40.out
printf "Test %d/45 complete \n" 40
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 7 -fy 5 -px 0.05 -py 0.2 -o test41.h5 > test41.out
printf "Test %d/45 complete \n" 41
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 7 -fy 5 -px 0.05 -py 0.2 -o test42.h5 > test42.out
printf "Test %d/45 complete \n" 42
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -g 0 -F 3 -a p -fx 7 -fy 5 -px 0.2 -py 0.05 -o test43.h5 > test43.out
printf "Test %d/45 complete \n" 43
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -C 0 -F 3 -a p -fx 7 -fy 5 -px 0.2 -py 0.05 -o test44.h5 > test44.out
printf "Test %d/45 complete \n" 44
prismatic -i ../SI100.XYZ -2D 0 20 -3D 1 -4D 1 -ps 1 -DPC 1 -F 3 -a p -fx 7 -fy 5 -px 0.2 -py 0.05 -o test45.h5 > test45.out
printf "Test %d/45 complete \n" 45

#clean up files
tail *.out
rm *.h5
rm *.out
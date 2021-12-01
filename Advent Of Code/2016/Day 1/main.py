def part1():
    key = "R1, L4, L5, L5, R2, R2, L1, L1, R2, L3, R4, R3, R2, L4, L2, R5, L1, R5, L5, L2, L3, L1, R1, R4, R5, L3, R2, L4, L5, R1, R2, L3, R3, L3, L1, L2, R5, R4, R5, L5, R1, L190, L3, L3, R3, R4, R47, L3, R5, R79, R5, R3, R1, L4, L3, L2, R194, L2, R1, L2, L2, R4, L5, L5, R1, R1, L1, L3, L2, R5, L3, L3, R4, R1, R5, L4, R3, R1, L1, L2, R4, R1, L2, R4, R4, L5, R3, L5, L3, R1, R1, L3, L1, L1, L3, L4, L1, L2, R1, L5, L3, R2, L5, L3, R5, R3, L4, L2, R2, R4, R4, L4, R5, L1, L3, R3, R4, R4, L5, R4, R2, L3, R4, R2, R1, R2, L4, L2, R2, L5, L5, L3, R5, L5, L1, R4, L1, R1, L1, R4, L5, L3, R4, R1, L3, R4, R1, L3, L1, R1, R2, L4, L2, R1, L5, L4, L5".split(", ")
    x = 0
    y = 0
    direction = 0
    for instruction in key:
        turn = instruction[0]
        distance = int(instruction[1:])
        if 'R' in turn:
            direction += 1
        else:
            direction -= 1
        if direction%4 == 0:
            y += distance
        elif direction%4 == 1:
            x += distance
        elif direction%4 == 2:
            y -= distance
        else:
            x -= distance
    print(abs(x) + abs(y))

def part2():
    key = "R1, L4, L5, L5, R2, R2, L1, L1, R2, L3, R4, R3, R2, L4, L2, R5, L1, R5, L5, L2, L3, L1, R1, R4, R5, L3, R2, L4, L5, R1, R2, L3, R3, L3, L1, L2, R5, R4, R5, L5, R1, L190, L3, L3, R3, R4, R47, L3, R5, R79, R5, R3, R1, L4, L3, L2, R194, L2, R1, L2, L2, R4, L5, L5, R1, R1, L1, L3, L2, R5, L3, L3, R4, R1, R5, L4, R3, R1, L1, L2, R4, R1, L2, R4, R4, L5, R3, L5, L3, R1, R1, L3, L1, L1, L3, L4, L1, L2, R1, L5, L3, R2, L5, L3, R5, R3, L4, L2, R2, R4, R4, L4, R5, L1, L3, R3, R4, R4, L5, R4, R2, L3, R4, R2, R1, R2, L4, L2, R2, L5, L5, L3, R5, L5, L1, R4, L1, R1, L1, R4, L5, L3, R4, R1, L3, R4, R1, L3, L1, R1, R2, L4, L2, R1, L5, L4, L5".split(", ")
    x = 0
    y = 0
    oldx = 0
    oldy = 0
    visited = ["0,0"]
    direction = 0
    for instruction in key:
        turn = instruction[0]
        distance = int(instruction[1:])
        if 'R' in turn:
            direction += 1
        else:
            direction -= 1
        if direction%4 == 0:
            oldy = y
            y += distance
        elif direction%4 == 1:
            oldx = x
            x += distance
        elif direction%4 == 2:
            oldy = y
            y -= distance
        else:
            oldx = x
            x -= distance
        kill = False
        if oldy != y:
            while True:
                if y < oldy:
                    oldy -= 1
                elif y > oldy:
                    oldy += 1
                if str(x)+","+str(oldy) in visited:
                    print(abs(x)+abs(oldy))
                    kill = True
                    break
                visited.append(str(x)+","+str(oldy))
                if y == oldy:
                    break
        else:
            while True:
                if x < oldx:
                    oldx -= 1
                elif x > oldx:
                    oldx += 1
                if str(oldx)+","+str(y) in visited:
                    print(abs(oldx)+abs(y))
                    kill = True
                    break
                visited.append(str(oldx)+","+str(y))
                if x == oldx:
                    break
        if kill:
            break
    

if __name__ == "__main__":
    #part1()
    part2()
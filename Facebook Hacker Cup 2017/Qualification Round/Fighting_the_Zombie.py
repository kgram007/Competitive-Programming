
def gen_coeff_table():
    (die_sides, w, h) = (6, 400, 20)
    coeff_table = [[[0 for x in range(w)] for y in range(h)] for ds in range(die_sides)]
    die_sides_map = {4:0, 6:1, 8:2, 10:3, 12:4, 20:5}

    for ds in die_sides_map.keys():
        for k in range(ds):
            coeff_table[die_sides_map[ds]][0][k] = 1

        for i in range(1,h):
            for j in range(w):
                for k in range(ds):
                    if j-k >= 0:
                        #print(str(die_sides_map[ds]) + " " + str(i) + " " + str(j) + " " + str(k))
                        coeff_table[die_sides_map[ds]][i][j] += coeff_table[die_sides_map[ds]][i-1][j-k]

    return (coeff_table, die_sides_map)

def parse_spell(spell_str):
    (X, rem) = spell_str.split('d')
    (Y, Z) = (0, 0)
    if rem.find('+') != -1:
        (Y, Z) = [int(i) for i in rem.split('+')]
    elif rem.find('-') != -1:
        (Y, Z) = [int(i) for i in rem.split('-')]
        Z = -Z
    else:
        (Y, Z) = (rem, 0)

    return (int(X), int(Y), int(Z))


def main():
    (die_sides, w, h) = (6, 400, 20)
    (coeff_table, die_sides_map) = gen_coeff_table()

    testcase_num = 1;
    T = int(input())
    while T > 0:
        (H, S) = [int(x) for x in input().split()]
        spells = [str(spell) for spell in input().split()]

        probs = [0.0];
        for spell in spells:
            (X, Y, Z) = parse_spell(spell)

            ds = die_sides_map[Y]
            total = 0;
            numerator = 0;
            start_index = (H - (X + Z))
            if start_index <= 0:
                probs.append(1.0)
                break
            else:
                for i in range(w):
                    if coeff_table[ds][X-1][i] == 0:
                        break
                    #print("i: " + str(i) + " " + str(coeff_table[ds][X-1][i]))
                    total += coeff_table[ds][X-1][i]
                    if i >= start_index:
                        numerator += coeff_table[ds][X-1][i]

                #print(str(numerator) + " " + str(total))
                probs.append(numerator/total)

        max_prob = max(probs)
        print('Case #{0}: {1:0.6f}'.format(testcase_num, max_prob))

        testcase_num += 1
        T = T - 1


main()

import random
import sys
import time
from copy import deepcopy
from xmlrpc.client import NOT_WELLFORMED_ERROR

random.seed(1)


class Result:

    def __init__(self, moves, connects):
        self.moves = moves
        self.connects = connects


class Solver:
    USED = 9
    VECS = [
        [0, 1],
        [0, -1],
        [1, 0],
        [-1, 0],
    ]

    def __init__(self, N, K, C):
        self.N = N
        self.K = K
        self.C = C
        self.LIM = K * 100
        self.cand = [40, 50, 55, 60, 70, 80, 90]
        self.comp_set = set()
        self.centloid = []
        self._init_comp_set()
        self._init_centloid()

    def _init_comp_set(self):
        for i in range(self.N):
            for j in range(self.N):
                if self.C[i][j] != 0:
                    self.comp_set.add((i, j))

    def _init_centloid(self):
        self.centloid.append([])
        if self.K == 2:
            self.centloid.append([self.N // 4, self.N // 4])
            self.centloid.append([3 * self.N // 4, 3 * self.N // 4])
        if self.K == 3:
            self.centloid.append([self.N // 4, self.N // 4])
            self.centloid.append([self.N // 4, 3 * self.N // 4])
            self.centloid.append([3 * self.N // 4, self.N // 2])
        if self.K == 4:
            self.centloid.append([self.N // 4, self.N // 4])
            self.centloid.append([self.N // 4, 3 * self.N // 4])
            self.centloid.append([3 * self.N // 4, self.N // 4])
            self.centloid.append([3 * self.N // 4, 3 * self.N // 4])
        if self.K == 5:
            self.centloid.append([self.N // 4, self.N // 4])
            self.centloid.append([self.N // 4, 3 * self.N // 4])
            self.centloid.append([3 * self.N // 4, self.N // 4])
            self.centloid.append([3 * self.N // 4, 2 * self.N // 4])
            self.centloid.append([3 * self.N // 4, 3 * self.N // 4])

    def _move(self, lim=None):
        if lim is None:
            lim = self.K * random.choice(self.cand)
        moves = []
        for _ in range(lim):
            (i, j) = random.sample(self.comp_set, 1)[0]
            if self.C[i][j] == 0:
                continue

            score_and_ij_list = []

            if random.randint(0, 6) <= 5:
                for di, dj in self.VECS:
                    # print(di, dj)
                    i2 = i + di
                    j2 = j + dj
                    if i2 < 0 or i2 >= self.N or j2 < 0 or j2 >= self.N:
                        continue
                    if self.C[i2][j2] != 0:
                        continue
                    score_and_ij_list.append([self.moved_score(i2, j2, self.C[i][j]), i2, j2])
            else:
                di, dj = random.choice(self.VECS)
                i2 = i + di
                j2 = j + dj
                if i2 < 0 or i2 >= self.N or j2 < 0 or j2 >= self.N:
                    continue
                if self.C[i2][j2] != 0:
                    continue
                score_and_ij_list.append([self.moved_score(i2, j2, self.C[i][j]), i2, j2])

            score_and_ij_list.sort()
            # print(score_and_ij_list)
            if len(score_and_ij_list) == 0:
                continue
            score, i2, j2 = score_and_ij_list[0]
            self.C[i2][j2] = self.C[i][j]
            self.C[i][j] = 0
            self.comp_set.remove((i, j))
            self.comp_set.add((i2, j2))
            moves.append([i, j, i2, j2])
        return moves

    def moved_score(self, i, j, color):
        score = 0
        cent_i, cent_j = self.centloid[color]
        # print(cent_i, cent_j)
        score = abs(i - cent_i) + abs(j - cent_j)
        return score

    def _connect(self, lim: int):
        connects = []

        def can_connect(i, j, v):
            i2 = i + v[0]
            j2 = j + v[1]
            while i2 < self.N and j2 < self.N:
                if self.C[i2][j2] == 0:
                    i2 += v[0]
                    j2 += v[1]
                    continue
                elif self.C[i2][j2] == self.C[i][j]:
                    return True
                return False
            return False

        def do_connect(i, j, v):
            i2 = i + v[0]
            j2 = j + v[1]
            while i2 < self.N and j2 < self.N:
                if self.C[i2][j2] == 0:
                    self.C[i2][j2] = self.USED
                elif self.C[i2][j2] == self.C[i][j]:
                    connects.append([i, j, i2, j2])
                    return
                else:
                    raise AssertionError()
                i2 += v[0]
                j2 += v[1]

        for i in range(self.N):
            for j in range(self.N):
                if self.C[i][j] in (0, self.USED):
                    continue
                for v in [[0, 1], [1, 0]]:
                    if can_connect(i, j, v):
                        do_connect(i, j, v)
                        if len(connects) >= lim:
                            return connects
        return connects

    def solve(self):
        # create random moves
        moves = self._move()
        # from each computer, connect to right and/or bottom if it will reach the same type
        connects = self._connect(self.LIM - len(moves))

        return Result(moves, connects)


class UnionFind:

    def __init__(self):
        self.parents = {}

    def find(self, x):
        if x not in self.parents:
            self.parents[x] = x
            return x
        elif self.parents[x] == x:
            return x
        else:
            self.parents[x] = self.find(self.parents[x])
            return self.parents[x]

    def unite(self, x, y):
        x = self.find(x)
        y = self.find(y)

        if x != y:
            self.parents[x] = y


def calc_score(N, K, C, res: Result):
    for v in res.moves:
        i, j, i2, j2 = v
        assert 1 <= C[i][j] <= K
        assert C[i2][j2] == 0
        C[i2][j2] = C[i][j]
        C[i][j] = 0

    uf = UnionFind()
    for v in res.connects:
        i, j, i2, j2 = v
        p1 = (i, j)
        p2 = (i2, j2)
        assert 1 <= C[i][j] <= K
        assert 1 <= C[i2][j2] <= K
        uf.unite(p1, p2)

    computers = []
    for i in range(N):
        for j in range(N):
            if 1 <= C[i][j] <= K:
                computers.append((i, j))

    score = 0
    for i in range(len(computers)):
        for j in range(i + 1, len(computers)):
            c1 = computers[i]
            c2 = computers[j]
            if uf.find(c1) != uf.find(c2):
                continue

            if C[c1[0]][c1[1]] == C[c2[0]][c2[1]]:
                score += 1
            else:
                score -= 1

    return max(score, 0)


def print_answer(res: Result):
    print(len(res.moves))
    for arr in res.moves:
        print(*arr)
    print(len(res.connects))
    for arr in res.connects:
        print(*arr)


def main():
    start_time = time.time()
    N, K = [int(v) for v in input().split(" ")]
    C = []

    for _ in range(N):
        C.append([int(v) for v in input()])

    max_score = 0
    global max_res
    score_list = []
    solve_time = 0
    calc_time = 0
    cnt = 0
    while True:
        end_time = time.time()
        if start_time + 2.5 > end_time:
            now_c = deepcopy(C)
            solver = Solver(N, K, now_c)
            now_res = solver.solve()
            now_score = calc_score(N, K, deepcopy(C), now_res)
            score_list.append(now_score)
            if max_score < now_score:
                max_res = now_res
                max_score = now_score
            cnt+= 1
        else:
            break

    print_answer(max_res)
    # print(max_score)

if __name__ == "__main__":
    main()

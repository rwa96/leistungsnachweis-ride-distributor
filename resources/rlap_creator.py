import numpy as np
from sys import argv
from scipy.optimize import linear_sum_assignment


def main(nRows, nCols, maxEntry=20):
    mat = np.random.randint(maxEntry, size=(nRows, nCols))
    maxVal = np.amax(mat)
    profitMat = maxVal - mat

    rows, cols = linear_sum_assignment(profitMat)
    elmSum = np.sum(mat[rows, cols])
    matStr = "{" + ", ".join([str(elm) for elm in np.concatenate(mat)]) + "}"

    print(f"{{Tensor<int>({{{nRows}, {nCols}}}, {matStr}), {elmSum}}}")


if __name__ == '__main__':
    main(*[int(elm) for elm in argv[1:]])

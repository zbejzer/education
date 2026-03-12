from math import sqrt

RING_POINTS = [10, 5, 1, 0]
RING_RADIUSES = [1, 5, 10]


def get_coordinates_modulus(x: int, y: int) -> float:
    return sqrt(x**2 + y**2)


def score(x: int, y: int) -> int:
    coordinates_modulus = get_coordinates_modulus(x, y)

    for i, v in enumerate(RING_RADIUSES):
        if coordinates_modulus <= v:
            return RING_POINTS[i]

    return 0

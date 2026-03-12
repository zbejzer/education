def leap_year(year: int) -> bool:
    if year % 4 != 0:
        return False

    if year % 100 == 0:
        return year % 400 == 0

    return True

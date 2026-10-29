lambda_m <- 1 / 73
lambda_k <- 1 / 81

# Gęstości i funkcje przeżycia
f_m <- function(t) dexp(t, lambda_m)
f_k <- function(t) dexp(t, lambda_k)
s_m <- function(t) exp(-lambda_m * t)
s_k <- function(t) exp(-lambda_k * t)

# a) Wykresy
op <- par(mfrow = c(1, 2))

curve(f_m, 0, 300, col = "blue")
curve(f_k, add = TRUE, col = "red")

curve(s_m, 0, 300, col = "blue")
curve(s_k, add = TRUE, col = "red")

# b) Wartość oczekiwana i odchylenie standardowe
# Dla Exp(lambda): E(T) = 1/lambda, Var(T) = 1/lambda^2, sd(T) = 1/lambda
wartosc_oczekiwana <- function(lambda) 1 / lambda
odchylenie_std <- function(lambda) sqrt(1 / lambda^2)

par(op)

print(
  data.frame(
    plec = c("mężczyźni", "kobiety"),
    lambda = c(lambda_m, lambda_k),
    wartosc_oczekiwana = c(
      wartosc_oczekiwana(lambda_m),
      wartosc_oczekiwana(lambda_k)
    ),
    odchylenie_std = c(odchylenie_std(lambda_m), odchylenie_std(lambda_k))
  )
)

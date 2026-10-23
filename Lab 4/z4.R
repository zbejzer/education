# ------------------------------------------------------------
# Wykorzystaj do modelowania długości życia rozkład wykładniczy. Średnia 
# długość życia na podstawie tablic życia z roku 2018 wynosi dla mężczyzn 
# 73 lata, dla kobiet 81 lat.
# a) Narysuj na jednym rysunku gęstości rozkładów wykładniczych Exp(1/73) 
#    i Exp(1/81) oraz na drugim funkcje przeżycia tych rozkładów.
# b) Oblicz wartości oczekiwane i odchylenia standardowe.
# ------------------------------------------------------------

lambda_m <- 1 / 73
lambda_k <- 1 / 81

# Gęstości i funkcje przeżycia
op <- par(mfrow = c(1, 2))

# Gęstości: f(t) = lambda * exp(-lambda * t)
curve(dexp(x, rate = lambda_m), from = 0, to = 300, n = 500,
      col = "blue", lwd = 2,
      ylim = c(0, 0.014),
      main = "Gęstości rozkładów wykładniczych",
      xlab = "t (lata)", ylab = "f(t)")
curve(dexp(x, rate = lambda_k), from = 0, to = 300, n = 500,
      col = "red", lwd = 2, add = TRUE)
legend("topright",
       legend = c("mężczyźni Exp(1/73)", "kobiety Exp(1/81)"),
       col = c("blue", "red"), lwd = 2, bty = "n")

# Funkcje przeżycia: S(t) = P(T > t) = exp(-lambda * t)
curve(pexp(x, rate = lambda_m, lower.tail = FALSE), from = 0, to = 300, n = 500,
      col = "blue", lwd = 2,
      main = "Funkcje przeżycia S(t) = P(T > t)",
      xlab = "t (lata)", ylab = "S(t)")
curve(pexp(x, rate = lambda_k, lower.tail = FALSE), from = 0, to = 300, n = 500,
      col = "red", lwd = 2, add = TRUE)
legend("topright",
       legend = c("mężczyźni Exp(1/73)", "kobiety Exp(1/81)"),
       col = c("blue", "red"), lwd = 2, bty = "n")

par(op)

# Wartość oczekiwana i odchylenie standardowe
# Dla Exp(lambda): E(T) = 1/lambda, Var(T) = 1/lambda^2, sd(T) = 1/lambda
wartosc_oczekiwana <- function(lambda) 1 / lambda
odchylenie_std     <- function(lambda) sqrt(1 / lambda^2)

wyniki <- data.frame(
  plec                = c("mężczyźni", "kobiety"),
  lambda              = c(lambda_m, lambda_k),
  wartosc_oczekiwana  = c(wartosc_oczekiwana(lambda_m), wartosc_oczekiwana(lambda_k)),
  odchylenie_std      = c(odchylenie_std(lambda_m), odchylenie_std(lambda_k))
)
print(wyniki, digits = 5)
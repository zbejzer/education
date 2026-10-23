# ------------------------------------------------------------
# Na jednym rysunku narysuj wykresy gęstości rozkładów N(0,1) i t(n), 
# dla n = 5, 10, 15, 20, 30. Jak zmienia się rozkład t-Studenta w stosunku 
# do rozkładu N(0,1) wraz ze wzrostem liczby stopni swobody n? Oblicz 
# wariancję dla rozkładu t-Studenta i porównaj z wariancją rozkładu N(0,1).
# ------------------------------------------------------------

stopnie <- c(5, 10, 15, 20, 30)
kolory <- c("red", "orange", "darkgreen", "blue", "purple")

# Wykres
curve(dnorm(x), from = -5, to = 5, n = 500,
      col = "black", lwd = 3,
      ylim = c(0, 0.42),
      main = "Gęstości N(0,1) i t-Studenta t(n)",
      xlab = "x", ylab = "gęstość")

for (i in seq_along(stopnie)) {
  curve(dt(x, df = stopnie[i]), from = -5, to = 5, n = 500,
        col = kolory[i], lwd = 2, lty = 2, add = TRUE)
}

legend("topright",
       legend = c("N(0,1)", paste0("t(", stopnie, ")")),
       col    = c("black", kolory),
       lwd    = c(3, rep(2, length(stopnie))),
       lty    = c(1, rep(2, length(stopnie))),
       bty    = "n")

# Wariancja
wariancja_t <- function(n) ifelse(n > 2, n / (n - 2), Inf)

wyniki <- data.frame(
  n              = stopnie,
  var_t_wzor     = wariancja_t(stopnie),
  var_N01        = 1
)
wyniki$roznica <- wyniki$var_t_wzor - wyniki$var_N01

print(wyniki, digits = 5)
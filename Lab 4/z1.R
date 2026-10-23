# ------------------------------------------------------------
# Wygeneruj próbę 1000-elementową: x_1, ..., x_1000 z rozkładu normalnego 
# X ~ N(0, 2^2). Dla każdej z wygenerowanych wartości oblicz: 
# y_i = exp(x_i), i = 1, ..., 1000. Narysuj na jednym rysunku histogram 
# danych y_1, ..., y_1000 oraz wykres gęstości rozkładu log-normalnego LN(0, 2^2). 
# Poeksperymentuj z innymi parametrami i długościami prób.
# ------------------------------------------------------------

set.seed(123)

rysuj_lognormal <- function(n = 1000, mu = 0, sigma = 2, k = 40, p_ucieto = 0.95) {
  
  # rnorm przyjmuje odchylenie standardowe, nie wariancję
  x <- rnorm(n, mean = mu, sd = sigma)
  y <- exp(x)
  
  # Rozkład log-normalny ma bardzo ciężki prawy ogon, więc oś X ucinamy
  # na kwantylu teoretycznym (p_ucieto), a ostatni przedział histogramu
  # obejmuje resztę obserwacji (słupki o różnej szerokości,
  # freq = FALSE zapewnia poprawną skalę gęstości).
  granica <- qlnorm(p_ucieto, meanlog = mu, sdlog = sigma)
  breaks  <- c(seq(0, granica, length.out = k), max(y, granica) + 1)
  
  hist(y,
       breaks = breaks,
       freq   = FALSE,
       xlim   = c(0, granica),
       col    = "lightblue",
       border = "white",
       main   = sprintf("LN(%g, %g^2): n = %d", mu, sigma, n),
       xlab   = "y",
       ylab   = "gęstość")
  
  # 3. Teoretyczna gęstość rozkładu log-normalnego
  curve(dlnorm(x, meanlog = mu, sdlog = sigma),
        from = 1e-6, to = granica,
        n = 1000, add = TRUE, col = "red", lwd = 2)
  
  legend("topright",
         legend = c("histogram próby", "gęstość LN"),
         fill   = c("lightblue", NA),
         border = c("white", NA),
         lty    = c(NA, 1), lwd = c(NA, 2),
         col    = c(NA, "red"),
         bty    = "n")
  
  invisible(y)
}

# n = 1000, X ~ N(0, 2^2)
rysuj_lognormal(n = 1000, mu = 0, sigma = 2)

# Eksperymenty
op <- par(mfrow = c(2, 3))

rysuj_lognormal(n = 100,    mu = 0, sigma = 2)
rysuj_lognormal(n = 1000,   mu = 0, sigma = 2)
rysuj_lognormal(n = 100000, mu = 0, sigma = 2, k = 80)

rysuj_lognormal(n = 1000, mu = 0, sigma = 0.5)
rysuj_lognormal(n = 1000, mu = 1, sigma = 1)
rysuj_lognormal(n = 1000, mu = -1, sigma = 1.5)

par(op)


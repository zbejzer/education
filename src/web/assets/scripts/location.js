const options = {
  enableHighAccuracy: true,
  timeout: 5000,
  maximumAge: 0,
};

function success(pos) {
  const crd = pos.coords;

  const locationDiv = document.getElementById("location");
  const subNavbarDiv = document.getElementById("sub-navbar");
  const locationText = document.createTextNode(` ${crd.latitude} ${crd.longitude}`);

  locationDiv.appendChild(locationText);
  subNavbarDiv.classList.remove("no-location");
}

function error(err) {
  console.warn(`ERROR(${err.code}): ${err.message}`);

  const locationDiv = document.getElementById("location");
  locationDiv.appendChild(document.createTextNode("Error"));
}

navigator.geolocation.getCurrentPosition(success, error, options);
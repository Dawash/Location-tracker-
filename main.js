function askForNotificationPermission() {
    Notification.requestPermission().then(function (permission) {
        if (permission === 'granted') {
            getLocation();
        }
    });
}

function getLocation() {
    if (navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(showPosition);
    }
}

function showPosition(position) {
    var latitude = position.coords.latitude;
    var longitude = position.coords.longitude;

    var locationLink = "https://example.com/location?lat=" + latitude + "&lon=" + longitude;
    alert('Your current location:\nLatitude: ' + latitude + '\nLongitude: ' + longitude);
    sendLocationLink(locationLink);
}

function sendLocationLink(link) {
    // Code to send the location link to the server or other actions you want to perform with the link.
    console.log("Location link sent: " + link);
}

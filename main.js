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
    alert('Your current location:\nLatitude: ' + position.coords.latitude + '\nLongitude: ' + position.coords.longitude);
}

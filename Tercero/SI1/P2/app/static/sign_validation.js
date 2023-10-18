

function formValidation() {
    
    var username = document.registration.username;
    var password = document.registration.password;
    var password2 = document.registration.password2;
    var email = document.registration.email;
    var creditcard = document.registration.creditCard;
    var address = document.registration.address;

    if (username_validation(username)) {
        if (password_validation(password, password2)) {
            if (email_validation(email)) {
                
                if (creditcard_validation(creditcard)) {
                    if (address_validation(address)) {
                       return true;
                    }
                }
            }
        }
    }
    return false;
}

function username_validation(username) {
    if (username.value.length < 6) {
        document.getElementById("errores").textContent = "Username should be at least 6 characters long";
        username.focus();
        return false;
    }
    re = /^[a-zA-Z0-9]*/;
    if (!re.test(username)) {
        document.getElementById("errores").textContent = "Username cannot contain special characters";
        username.focus();
        return false;
    }

    return true;
}

function password_validation(password, password2) {


    if (password.value != password2.value) {
        document.getElementById("errores").textContent = "Passwords are not equal";
        username.focus();
        return false;
    }
    if (password.value.length < 8) {
        document.getElementById("errores").textContent = "Password should be at least 8 characters long";
        username.focus();
        return false;
    }
    return true;
}

function email_validation(email) {
    
    
    //     re2=/^[a-zA-Z0-9\._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]/;


    if (email.value.indexOf("@") == -1) {
        email.focus();
        document.getElementById("errores").textContent = "Please enter a valid email";
        return false;
    }
    return true;
}

function creditcard_validation(creditcard) {

    if (creditcard.value.length != 16) {
        document.getElementById("errores").textContent = "Please enter a valid credit card";
        creditcard.focus();
        return false;
    }
    return true;
}

function address_validation(address) {
    if (address.value.length>50) {
        document.getElementById("errores").textContent = "Address cant be longer than 50 characters";
        address.focus();
        return false;
    }
    return true;
}



var strength = {
    0: "Worst",
    1: "Bad",
    2: "Weak",
    3: "Good",
    4: "Strong"
}

/*

function meter_update(value) {
    var password = document.getElementById('password');
    var meter = document.getElementById('passwordStrength');
    var text = document.getElementById('passwordStrengthText');

    var val = 0
    if (password.value.length > 8 ) val++;
    if (password.value.length > 20 ) val++;
    re = /^[<>'\"/;`%#\$]*$/;
    if (re.test(username)) val++;
    re = /[A-Z]/;
    if (re.test(username)) val++;
    
    // var result = zxcvbn(val);   
    // Update the password strength meter
    meter.value = val;
    // Update the text indicator
    if (val !== "") {
      text.innerHTML = "Strength: " + strength[val]; 
    } else {
      text.innerHTML = "";
    }
}

*/

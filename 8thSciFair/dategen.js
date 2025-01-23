// Function to generate a random integer between min and max (inclusive)
function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

// Function to get the number of days in a given month and year
function getDaysInMonth(month, year) {
    return new Date(year, month, 0).getDate();
}

// Function to generate a random date between 2000 and 2025
function generateRandomDate() {
    const year = getRandomInt(2000, 2025);
    const month = getRandomInt(1, 12);
    const day = getRandomInt(1, getDaysInMonth(month, year));
    
    // Format with leading zeros
    const formattedDay = day.toString().padStart(2, '0');
    const formattedMonth = month.toString().padStart(2, '0');
    
    return `${formattedDay}/${formattedMonth}/${year}`;
}

// Generate specified number of dates
function generateDates(count) {
    const dates = [];
    for (let i = 0; i < count; i++) {
        dates.push(generateRandomDate());
    }
    return dates;
}

// Get command line arguments
if (Deno.args.length !== 1) {
    console.error('Usage: deno run dategen.js <number_of_dates>');
    Deno.exit(1);
}

const numDates = parseInt(Deno.args[0]);

if (isNaN(numDates) || numDates <= 0) {
    console.error('Please provide a valid positive number');
    Deno.exit(1);
}

// Generate and print dates
const dates = generateDates(numDates);
dates.forEach(date => console.log(date));

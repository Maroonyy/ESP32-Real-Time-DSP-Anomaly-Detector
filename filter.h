// --- The Low-Pass Filter ---
float apply_low_pass_filter(float current_reading) {
    static float previous_reading = 0.0;
    float filtered_output = 0.5 * current_reading + 0.5 * previous_reading;
    previous_reading = current_reading; 
    return filtered_output;
}

// --- The Power Calculator ---
#define WINDOW_SIZE 10

float calculate_window_power(float new_filtered_sample) {
    static float power_buffer[WINDOW_SIZE] = {0}; 
    static int write_index = 0;
    
    // Push the newest sample into the buffer
    power_buffer[write_index] = new_filtered_sample;
    
    // Move the pointer forward and wrap it around
    write_index++;
    if (write_index >= WINDOW_SIZE) {
        write_index = 0;
    }
    
    // Calculate the total sum of squares
    float total_sum_of_squares = 0.0;
    
    for (int i = 0; i < WINDOW_SIZE; i++) {
      total_sum_of_squares += power_buffer[i] * power_buffer[i];
    }
    
    // Divide by N to get the average power
    float power = total_sum_of_squares / WINDOW_SIZE;
    
    return power;
}
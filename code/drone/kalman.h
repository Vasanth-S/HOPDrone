/**
 * kalman.h
 * Functions for Unscented Kalman Filtering
 */

#include "arm_math.h"

#define DIMENSIONS      6
#define NR_SIGMAPOINTS  2*DIMENSIONS+1

#define ALPHA           0.001
#define BETA            2
#define KAPPA           ALPHA*ALPHA*DIMENSIONS - DIMENSIONS

#define WEIGHTS         1/(2*(DIMENSIONS + KAPPA))  // Weight factors i > 0
#define WEIGHT_M0       KAPPA/(DIMENSIONS + KAPPA)  // Weight factor W_m for i = 0
#define WEIGHT_C0       KAPPA/(DIMENSIONS + KAPPA) - (1 - ALPHA*ALPHA + BETA) // Weight factor W_c for i = 0

// TODO: fix time or measure
#define DELTAT          0.1


/**
 * Position struct
 * Wrapper around 1 x 6 matrix
 *
 * index - value
 * 0 - x coordinate
 * 1 - y coordinate
 * 2 - z coordinate
 * 3 - x velocity
 * 4 - y velocity
 * 5 - z velocity
 */
typedef arm_matrix_instance_f32 position_t;

/**
 * Initialize constant weight factors
 * weight_m - arm_matrix_instance_f32 pointer (1x6)
 * weight_c - arm_matrix_instance_f32 pointer (1x6)
 */
void kalman_init_weight_factors(arm_matrix_instance_f32* weight_m, arm_matrix_instance_f32* weight_c);

/**
 * Initialize the postition vector
 * position - position_t pointer
 */
void kalman_init_position(position_t* position);

/**
 * Initialize array of sigmapoints
 * sigmapoints - array of position_t of size NR_SIGMAPOINTS
 */
void kalman_init_sigmapoints(position_t* sigmapoints);

/**
 * Initialize and populate F matrix
 * f_matrix - arm_matrix_instance_f32 pointer
 */
void kalman_init_f_matrix(arm_matrix_instance_f32* f_matrix);

/**
 * Initialize and populate G matrix
 * g_matrix - arm_matrix_instance_f32 pointer
 */
void kalman_init_g_matrix(arm_matrix_instance_f32* g_matrix);

/**
 * Initialize a DIMENSIONS x DIMENSIONS matrix
 * matrix - arm_matrix_instance_f32 pointer
 */
void kalman_init_dimensional_matrix(arm_matrix_instance_f32* matrix);

/**
 * Prediction step for Kalman filter
 */
void kalman_predict(void);

/**
 * Calculate Sigmapoints
 *
 * nr_points   - Number of sigmapoints
 * sigmapoints - Array of position_t with sigmapoints
 * mkmin       - position_t of best estimate
 * pkmin       - arm_matrix_instance_f32 with the variances
 *
 * Updates sigmapoints
 */
void kalman_update_sigmapoints(int nr_points, position_t* sigmapoints, position_t mkmin, arm_matrix_instance_f32 pkmin);

/**
 * Cholesky decomposition
 * see: http://rosettacode.org/wiki/Cholesky_decomposition#C
 * matrix - arm_matrix_instance_f32 to be decomposed
 * output - arm_matrix_instance_f32 pointer to the decomposed matrix
 */
void cholesky_decomp(arm_matrix_instance_f32 matrix, arm_matrix_instance_f32* output);

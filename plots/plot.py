import matplotlib.pyplot as plt
import numpy as np

A = [

[555.208, 530.409, 507.631, 486.906, 468.235, 451.591, 436.923, 424.158, 413.212, 403.990, 396.393, 390.329, 385.711, 382.468, 380.544, 379.907, 380.544, 382.468, 385.712, 390.33, 396.394, 403.99, 413.213, 424.159, 436.923, 451.592, 468.236, 486.907, 507.632, 530.409, 555.209, ],
[530.409, 504.656, 481.002, 459.48, 440.0910, 422.806, 407.574, 394.319, 382.951, 373.374, 365.486, 359.188, 354.393, 351.024, 349.027, 348.365, 349.027, 351.024, 354.393, 359.189, 365.486, 373.375, 382.952, 394.319, 407.574, 422.807, 440.091, 459.48, 481.003, 504.656, 530.41, ],
[507.631, 481.002, 456.543, 434.289, 414.24, 396.3680, 380.617, 366.911, 355.157, 345.254, 337.097, 330.585, 325.626, 322.143, 320.078, 319.393, 320.078, 322.143, 325.626, 330.585, 337.097, 345.254, 355.157, 366.911, 380.618, 396.368, 414.241, 434.29, 456.544, 481.003, 507.632,] ,
[486.906, 459.480, 434.289, 411.368, 390.719, 372.312, 356.090, 341.973, 329.867, 319.667, 311.266, 304.559, 299.451, 295.864, 293.737, 293.032, 293.737, 295.864, 299.452, 304.559, 311.266, 319.667, 329.867, 341.973, 356.09, 372.313, 390.72, 411.369, 434.29, 459.481, 486.907, ],
[468.235, 440.090, 414.240, 390.719, 369.529, 350.640, 333.992, 319.506, 307.083, 296.615, 287.994, 281.111, 275.87, 272.189, 270.005, 269.282, 270.006, 272.189, 275.87, 281.111, 287.994, 296.616, 307.083, 319.506, 333.993, 350.641, 369.53, 390.72, 414.241, 440.091, 468.236, ],
[451.591, 422.806, 396.368, 372.312, 350.640, 331.320, 314.294, 299.477, 286.771, 276.066, 267.248, 260.208, 254.848, 251.083, 248.85, 248.11, 248.85, 251.083, 254.848, 260.209, 267.248, 276.066, 286.772, 299.478, 314.295, 331.321, 350.641, 372.313, 396.369, 422.807, 451.592, ],
[436.922, 407.574, 380.617, 356.089, 333.992, 314.294, 296.933, 281.826, 268.871, 257.955, 248.964, 241.786, 236.32, 232.481, 230.204, 229.45, 230.204, 232.481, 236.32, 241.786, 248.964, 257.955, 268.871, 281.827, 296.934, 314.295, 333.993, 356.09, 380.618, 407.575, 436.923, ],
[424.158, 394.318, 366.911, 341.973, 319.506, 299.477, 281.826, 266.466, 253.293, 242.195, 233.053, 225.755, 220.197, 216.293, 213.978, 213.211, 213.978, 216.293, 220.197, 225.755, 233.053, 242.195, 253.294, 266.466, 281.827, 299.478, 319.506, 341.973, 366.912, 394.32, 424.159, ],
[413.212, 382.951, 355.157, 329.867, 307.083, 286.771, 268.871, 253.293, 239.935, 228.679, 219.408, 212.006, 206.37, 202.411, 200.063, 199.285, 200.063, 202.411, 206.37, 212.006, 219.408, 228.679, 239.935, 253.294, 268.871, 286.772, 307.083, 329.868, 355.158, 382.952, 413.213, ],
[403.990, 373.374, 345.254, 319.667, 296.615, 276.066, 257.955, 242.195, 228.679, 217.291, 207.911, 200.422, 194.719, 190.714, 188.339, 187.551, 188.339, 190.714, 194.72, 200.422, 207.911, 217.291, 228.679, 242.195, 257.956, 276.067, 296.616, 319.668, 345.255, 373.375, 403.991, ],
[396.394, 365.486, 337.097, 311.266, 287.994, 267.248, 248.964, 233.053, 219.408, 207.911, 198.441, 190.88, 185.123, 181.079, 178.681, 177.886, 178.681, 181.079, 185.123, 190.881, 198.441, 207.911, 219.408, 233.053, 248.965, 267.249, 287.995, 311.267, 337.098, 365.487, 396.395,] ,
[390.329, 359.188, 330.585, 304.559, 281.111, 260.208, 241.786, 225.755, 212.006, 200.422, 190.880, 183.262, 177.461, 173.387, 170.97, 170.17, 170.971, 173.387, 177.462, 183.263, 190.881, 200.422, 212.007, 225.755, 241.787, 260.209, 281.112, 304.56, 330.586, 359.189, 390.33, ],
[385.711, 354.393, 325.626, 299.451, 275.870, 254.848, 236.320, 220.197, 206.370, 194.719, 185.123, 177.461, 171.627, 167.529, 165.099, 164.294, 165.099, 167.529, 171.627, 177.462, 185.123, 194.72, 206.37, 220.197, 236.321, 254.848, 275.871, 299.452, 325.627, 354.394, 385.712, ],
[382.468, 351.024, 322.143, 295.864, 272.189, 251.083, 232.481, 216.293, 202.411, 190.714, 181.079, 173.387, 167.529, 163.415, 160.975, 160.166, 160.975, 163.415, 167.529, 173.387, 181.079, 190.714, 202.411, 216.294, 232.481, 251.083, 272.189, 295.865, 322.144, 351.025, 382.469, ],
[380.544, 349.027, 320.078, 293.737, 270.005, 248.850, 230.204, 213.978, 200.063, 188.338, 178.681, 170.970, 165.099, 160.975, 158.529, 157.719, 158.529, 160.975, 165.099, 170.971, 178.681, 188.339, 200.064, 213.979, 230.205, 248.85, 270.006, 293.738, 320.079, 349.028, 380.545,] ,
[379.907, 348.365, 319.393, 293.032, 269.282, 248.110, 229.450, 213.211, 199.285, 187.551, 177.886, 170.170, 164.294, 160.166, 157.719, 156.908, 157.719, 160.166, 164.294, 170.17, 177.887, 187.552, 199.286, 213.212, 229.45, 248.11, 269.283, 293.033, 319.394, 348.366, 379.908, ],
[380.544, 349.027, 320.078, 293.737, 270.006, 248.850, 230.204, 213.978, 200.063, 188.338, 178.681, 170.970, 165.099, 160.975, 158.529, 157.719, 158.529, 160.975, 165.099, 170.971, 178.681, 188.339, 200.064, 213.979, 230.205, 248.85, 270.006, 293.737, 320.079, 349.028, 380.545, ],
[382.468, 351.025, 322.143, 295.864, 272.189, 251.083, 232.481, 216.293, 202.411, 190.714, 181.079, 173.387, 167.529, 163.415, 160.975, 160.166, 160.975, 163.415, 167.529, 173.387, 181.079, 190.714, 202.411, 216.294, 232.482, 251.083, 272.189, 295.865, 322.144, 351.025, 382.469, ],
[385.711, 354.393, 325.626, 299.451, 275.870, 254.848, 236.320, 220.197, 206.370, 194.719, 185.123, 177.461, 171.627, 167.529, 165.099, 164.294, 165.099, 167.529, 171.627, 177.462, 185.123, 194.72, 206.37, 220.198, 236.321, 254.848, 275.87, 299.452, 325.627, 354.393, 385.712, ],
[390.329, 359.188, 330.585, 304.559, 281.111, 260.208, 241.786, 225.755, 212.006, 200.422, 190.88, 183.262, 177.461, 173.387, 170.971, 170.17, 170.971, 173.387, 177.462, 183.263, 190.881, 200.423, 212.007, 225.755, 241.787, 260.209, 281.112, 304.559, 330.585, 359.189, 390.33, ],
[396.394, 365.486, 337.097, 311.266, 287.994, 267.248, 248.964, 233.053, 219.408, 207.911, 198.441, 190.88, 185.123, 181.079, 178.681, 177.886, 178.681, 181.079, 185.123, 190.881, 198.441, 207.911, 219.408, 233.053, 248.965, 267.249, 287.995, 311.266, 337.097, 365.486, 396.394, ],
[403.990, 373.375, 345.254, 319.667, 296.616, 276.066, 257.955, 242.195, 228.679, 217.291, 207.911, 200.422, 194.719, 190.714, 188.339, 187.552, 188.339, 190.714, 194.72, 200.422, 207.911, 217.291, 228.679, 242.195, 257.956, 276.067, 296.616, 319.668, 345.254, 373.375, 403.99, ],
[413.213, 382.952, 355.157, 329.867, 307.083, 286.772, 268.871, 253.293, 239.935, 228.679, 219.408, 212.006, 206.37, 202.411, 200.063, 199.285, 200.063, 202.411, 206.37, 212.006, 219.408, 228.679, 239.935, 253.294, 268.871, 286.772, 307.083, 329.867, 355.157, 382.952, 413.213, ],
[424.159, 394.319, 366.911, 341.973, 319.506, 299.478, 281.826, 266.466, 253.293, 242.195, 233.053, 225.754, 220.197, 216.293, 213.978, 213.211, 213.978, 216.293, 220.197, 225.755, 233.053, 242.195, 253.294, 266.466, 281.827, 299.478, 319.506, 341.973, 366.911, 394.319, 424.159, ],
[436.923, 407.574, 380.617, 356.090, 333.992, 314.294, 296.933, 281.826, 268.871, 257.955, 248.964, 241.786, 236.32, 232.481, 230.204, 229.45, 230.204, 232.481, 236.32, 241.786, 248.964, 257.955, 268.871, 281.827, 296.934, 314.295, 333.993, 356.09, 380.618, 407.574, 436.923, ],
[451.591, 422.807, 396.368, 372.312, 350.640, 331.321, 314.294, 299.477, 286.771, 276.066, 267.248, 260.208, 254.848, 251.082, 248.85, 248.11, 248.85, 251.083, 254.848, 260.209, 267.248, 276.066, 286.772, 299.478, 314.295, 331.321, 350.641, 372.313, 396.368, 422.807, 451.591, ],
[468.235, 440.091, 414.240, 390.720, 369.530, 350.640, 333.992, 319.506, 307.082, 296.615, 287.994, 281.111, 275.87, 272.188, 270.005, 269.282, 270.005, 272.189, 275.87, 281.111, 287.994, 296.616, 307.083, 319.506, 333.993, 350.641, 369.53, 390.72, 414.241, 440.091, 468.235, ],
[486.906, 459.480, 434.289, 411.369, 390.719, 372.312, 356.089, 341.973, 329.867, 319.667, 311.266, 304.559, 299.451, 295.864, 293.737, 293.032, 293.737, 295.864, 299.451, 304.559, 311.266, 319.667, 329.867, 341.973, 356.09, 372.313, 390.72, 411.369, 434.289, 459.48, 486.906, ],
[507.631, 481.002, 456.543, 434.289, 414.240, 396.368, 380.617, 366.911, 355.157, 345.254, 337.097, 330.585, 325.626, 322.143, 320.078, 319.393, 320.078, 322.143, 325.626, 330.585, 337.097, 345.254, 355.157, 366.911, 380.618, 396.368, 414.241, 434.289, 456.543, 481.002, 507.631,], 
[530.409, 504.656, 481.002, 459.480, 440.091, 422.806, 407.574, 394.319, 382.951, 373.374, 365.486, 359.188, 354.393, 351.024, 349.027, 348.365, 349.027, 351.025, 354.393, 359.189, 365.486, 373.375, 382.952, 394.319, 407.574, 422.807, 440.091, 459.48, 481.002, 504.656, 530.409,] ,
[555.208, 530.409, 507.631, 486.906, 468.235, 451.591, 436.923, 424.158, 413.212, 403.99, 396.394, 390.329, 385.711, 382.468, 380.544, 379.907, 380.545, 382.468, 385.712, 390.33, 396.394, 403.99, 413.213, 424.159, 436.923, 451.591, 468.235, 486.906, 507.631, 530.409, 555.208,] 
]


B = [
555.208,
504.656,
456.543,
411.368,
369.529,
331.32,
296.933,
266.466,
239.935,
217.291,
198.441,
183.262,
171.627,
163.415,
158.529,
156.908,
158.529,
163.415,
171.627,
183.263,
198.441,
217.291,
239.935,
266.466,
296.934,
331.321,
369.53,
411.369,
456.543,
504.656,
555.208,

]

# plt.imshow(A, cmap="jet")

# Plot a colorbar with label.
# cb = plt.colorbar()
# cb.set_label('Temperatura')

plt.plot(B)

# Add title and labels to plot.
plt.xlabel('(x, x)')
plt.ylabel('Temperatura')

# Show the plot.
plt.show()
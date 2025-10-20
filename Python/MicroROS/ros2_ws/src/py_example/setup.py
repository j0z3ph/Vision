from setuptools import find_packages, setup

package_name = 'py_example'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jlcruz',
    maintainer_email='jlcruz@ipn.mx',
    description='Ejemplo de un publisher simple',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'simple_publisher = py_example.simple_publisher:main',
            'simple_subscriber = py_example.simple_subscriber:main',
        ],
    },
)

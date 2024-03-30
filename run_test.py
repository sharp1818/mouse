import subprocess
import os

def run_test():
    try:
        subprocess.run(['python', 'MovementTesting.py'], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error al ejecutar el script MovementTesting.py: {e}")
        # Desactivar entorno virtual
        deactivate_venv()
        
def activate_venv():
    activate_path = os.path.join('myenv', 'Scripts', 'activate')
    subprocess.run([activate_path], shell=True)
    
def deactivate_venv():
    deactivate_path = os.path.join('myenv', 'Scripts', 'deactivate')
    subprocess.run([deactivate_path], shell=True)
if __name__ == "__main__":
    activate_venv()
    run_test()

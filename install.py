import subprocess
import os
import platform
import requests
import os

def install_git():
    # Verificar si Git está instalado
    try:
        subprocess.run(['git', '--version'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=True)
        print("Git already installed.")
    except subprocess.CalledProcessError:
        # Si Git no está instalado, instalarlo
        print("Installing Git...")
        subprocess.run(['winget', 'install', '--id', 'Git.Git', '-e', '--source', 'winget'], check=True)

def install_python():
    # Verificar si Python está instalado
    try:
        subprocess.run(['python', '--version'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=True)
        print("Python already installed.")
    except subprocess.CalledProcessError:
        # Si Python no está instalado, instalarlo
        print("Installing Python...")
        if platform.system() == 'Windows':
            # Descargar el instalador de Python desde python.org
            python_download_url = 'https://www.python.org/ftp/python/3.12.2/python-3.12.2-amd64.exe'
            python_installer_path = 'python_installer.exe'
            print("Downloading Python installer...")
            response = requests.get(python_download_url)
            with open(python_installer_path, 'wb') as f:
                f.write(response.content)
            # Ejecutar el instalador descargado
            print("Running Python installer...")
            subprocess.run([python_installer_path, '/quiet', 'InstallAllUsers=1', 'PrependPath=1'], check=True)
            print("Python installed successfully.")
            # Eliminar el instalador después de la instalación
            os.remove(python_installer_path)
        else:
            print("Python installation is not supported on this platform.")
            
if __name__ == "__main__":
    # Instalar Git si no está instalado
    install_git()
    
    # Instalar Python si no está instalado
    install_python()
    
    # Crear y activar un entorno virtual
    subprocess.run(['python', '-m', 'venv', 'myenv'], check=True)
    activate_path = os.path.join('myenv', 'Scripts', 'activate')
    subprocess.run([activate_path], shell=True)
    
    try:
        # Instalar las dependencias desde el archivo requirements.txt
        print("Installing dependencies...")
        subprocess.run(['pip', 'install', '-r', 'requirements.txt'], check=True)
        print("Dependencies installed successfully.")
    finally:
        deactivate_path = os.path.join('myenv', 'Scripts', 'deactivate')
        subprocess.run([deactivate_path], shell=True)
    
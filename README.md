
install GCM https://github.com/git-ecosystem/git-credential-manager/releases
tar -xvzf gcm-linux_amd64.2.6.0.tar.gz
./git-credential-manager configure
./git-credential-manager --version
git config --global credential.credentialStore secretservice

sudo apt install git
git init
git config --local user.email "iamgauravg@gmail.com"
git config --local user.name "Gaurav Gupta"
git add .
git status
git commit
git log
git remote add origin git@github.com:iamgauravg/nsumo_gg.git
git remote set-url origin https://github.com/iamgauravg/nsumo_gg.git
git push -u origin main


git submodule add https://github.com/mpaland/printf.git external/printf
